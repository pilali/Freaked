/*
    Compares the current Granulator against the LV2 build that runs on the MOD.

    The DSP sources are compiled by whatever Faust is installed, and a compiler
    a decade newer than the one that produced the shipped LV2 can quietly
    change what an expression means. That is not hypothetical: `2^32 - 1` folded
    to 4294967295 in 2016 and folds to -1 today, which turned the granulator's
    position randomiser into a negation and destroyed the effect without
    failing a single structural test.

    So this pins behaviour rather than structure. Both implementations get the
    same input and settings, and their output energy is compared second by
    second. An exact match is not expected -- the current source carries
    deliberate fixes, and two Faust versions order arithmetic differently -- but
    the shape of the output has to be the same.
*/

#include "reference/LegacyGranulator.hpp"

#include <faust/dsp/dsp.h>
#include <faust/gui/UI.h>
#include <faust/gui/meta.h>
#include "GranulatorDSP.hpp"

#include <cmath>
#include <cstdio>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace
{
    constexpr int sampleRate = 48000;
    constexpr int blockSize  = 512;

    template <typename Base, typename Float>
    struct ZoneCollector : Base
    {
        std::vector<std::pair<std::string, Float*>> zones;

        void addHorizontalSlider (const char* label, Float* zone, Float init, Float, Float, Float) override
        { *zone = init; zones.emplace_back (label, zone); }
        void addVerticalSlider (const char* label, Float* zone, Float init, Float, Float, Float) override
        { *zone = init; zones.emplace_back (label, zone); }
        void addNumEntry (const char* label, Float* zone, Float init, Float, Float, Float) override
        { *zone = init; zones.emplace_back (label, zone); }
    };

    struct CurrentCollector : ZoneCollector<UI, FAUSTFLOAT>
    {
        void openTabBox (const char*) override {}
        void openHorizontalBox (const char*) override {}
        void openVerticalBox (const char*) override {}
        void closeBox() override {}
        void addButton (const char*, FAUSTFLOAT*) override {}
        void addCheckButton (const char*, FAUSTFLOAT*) override {}
        void addHorizontalBargraph (const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) override {}
        void addVerticalBargraph (const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) override {}
        void addSoundfile (const char*, const char*, Soundfile**) override {}
    };

    using LegacyCollector = ZoneCollector<oldgran::UI, float>;

    template <typename Zones>
    void setZone (const Zones& zones, const std::string& name, float value)
    {
        for (const auto& zone : zones)
            if (zone.first == name)
                *zone.second = value;
    }

    struct Settings
    {
        const char* name;
        float delayLength, grainLength, grainDensity, mix;
    };
}

/** Returns true when the current build still matches the reference. */
bool runLegacyGranulatorComparison()
{
    std::printf ("\nGranulator against the LV2 reference build\n");

    bool allMatched = true;

    // The grain lengths stay above about 0.06 s on purpose. The reference is
    // the 2016 build, which still carries the division by zero this project
    // fixed: its grain counter divides by int(sampleRate * grainLength) while
    // the parameter smoother is still ramping up from zero, so asking it for
    // the shortest grains crashes it before it can render anything. That the
    // reference cannot be driven there is itself the bug report for the LV2.
    const Settings cases[] = {
        { "defaults",         10.0f, 0.10f,  2.0f, 0.5f },
        { "dense, fully wet",  4.0f, 0.07f, 16.0f, 1.0f },
        { "long grains",       2.0f, 0.30f,  8.0f, 1.0f },
    };

    for (const auto& settings : cases)
    {
        auto legacyOwned  = std::make_unique<oldgran::Granulator>();
        auto currentOwned = std::make_unique<GranulatorDSP>();

        legacyOwned->init (sampleRate);
        currentOwned->init (sampleRate);

        LegacyCollector  legacyUi;   legacyOwned->buildUserInterface (&legacyUi);
        CurrentCollector currentUi;  currentOwned->buildUserInterface (&currentUi);

        for (const auto& control : { std::make_pair ("delay length",  settings.delayLength),
                                     std::make_pair ("grain length",  settings.grainLength),
                                     std::make_pair ("grain density", settings.grainDensity),
                                     std::make_pair ("mix",           settings.mix) })
        {
            setZone (legacyUi.zones,  control.first, control.second);
            setZone (currentUi.zones, control.first, control.second);
        }

        std::vector<float> inputLeft (blockSize), inputRight (blockSize);
        std::vector<float> legacyLeft (blockSize), legacyRight (blockSize);
        std::vector<float> currentLeft (blockSize), currentRight (blockSize);

        float* legacyIn[2]  = { inputLeft.data(), inputRight.data() };
        float* legacyOut[2] = { legacyLeft.data(), legacyRight.data() };
        FAUSTFLOAT* currentIn[2]  = { inputLeft.data(), inputRight.data() };
        FAUSTFLOAT* currentOut[2] = { currentLeft.data(), currentRight.data() };

        double phase = 0.0;
        long sampleIndex = 0;
        double worstRatio = 1.0;
        int worstSecond = -1;

        // Long enough for the ten second delay line to fill and start repeating.
        constexpr int seconds = 16;

        for (int second = 0; second < seconds; ++second)
        {
            double legacyEnergy = 0.0, currentEnergy = 0.0;
            long counted = 0;

            for (int block = 0; block < sampleRate / blockSize; ++block)
            {
                for (int i = 0; i < blockSize; ++i)
                {
                    // A tone that steps up in pitch every second, so the delay
                    // line holds something that changes over time.
                    const double t = double (sampleIndex + i) / sampleRate;
                    const double frequency = 220.0 * std::pow (2.0, std::floor (t) / 3.0);
                    phase += frequency / sampleRate;
                    const auto value = static_cast<float> (0.4 * std::sin (6.283185307 * phase));
                    inputLeft[i]  = value;
                    inputRight[i] = value;
                }

                sampleIndex += blockSize;

                legacyOwned->compute (blockSize, legacyIn, legacyOut);
                currentOwned->compute (blockSize, currentIn, currentOut);

                for (int i = 0; i < blockSize; ++i)
                {
                    legacyEnergy  += double (legacyLeft[i])  * legacyLeft[i];
                    currentEnergy += double (currentLeft[i]) * currentLeft[i];
                    ++counted;
                }
            }

            const auto legacyRms  = std::sqrt (legacyEnergy / double (counted));
            const auto currentRms = std::sqrt (currentEnergy / double (counted));

            // The first seconds are dominated by the delay line filling up and
            // by the parameter smoothers, where the two builds legitimately
            // differ; score once the effect is running steadily.
            if (second < 4 || legacyRms < 1.0e-3)
                continue;

            const auto ratio = currentRms > 0.0 ? currentRms / legacyRms : 0.0;

            if (std::abs (std::log (ratio > 0.0 ? ratio : 1.0e-9))
                > std::abs (std::log (worstRatio)))
            {
                worstRatio = ratio;
                worstSecond = second;
            }
        }

        // Half to double covers Faust version differences and the deliberate
        // fixes, while the noise normalisation regression was off by three
        // times and near silent in other conditions.
        const bool matched = worstRatio > 0.5 && worstRatio < 2.0;
        allMatched = allMatched && matched;

        std::printf ("    %-4s %-18s worst deviation %.2fx (second %d)\n",
                     matched ? "ok" : "FAIL", settings.name, worstRatio, worstSecond);
    }

    return allMatched;
}
