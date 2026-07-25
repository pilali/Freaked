#pragma once

#include <faust/gui/UI.h>
#include <juce_core/juce_core.h>

#include <vector>

/**
    One control exposed by a Faust DSP, together with every memory zone that
    backs it.

    There is one zone per DSP instance: a mono Faust DSP running on a stereo
    track is instantiated twice, and both copies have to see the same value.
*/
struct FaustParameter
{
    juce::String label;                 // the label as written in the .dsp file
    juce::String id;                    // stable, host facing identifier
    float defaultValue = 0.0f;
    float minValue     = 0.0f;
    float maxValue     = 1.0f;
    float step         = 0.0f;          // 0 means continuous
    bool  isToggle     = false;
    std::vector<FAUSTFLOAT*> zones;
};

/**
    Walks the user interface a Faust DSP declares and records its controls.

    Faust emits its UI in a deterministic order for a given DSP class, so the
    n-th entry always describes the same control across instances. That is what
    lets the processor line up the zones of several instances by index.
*/
class FaustParameterCollector : public UI
{
public:
    struct Entry
    {
        juce::String label;
        FAUSTFLOAT*  zone = nullptr;
        float defaultValue = 0.0f, minValue = 0.0f, maxValue = 1.0f, step = 0.0f;
        bool  isToggle = false;
    };

    const std::vector<Entry>& getEntries() const noexcept { return entries; }

    // -- layout: the Freaked plugins are flat, so grouping is simply ignored
    void openTabBox        (const char*) override {}
    void openHorizontalBox (const char*) override {}
    void openVerticalBox   (const char*) override {}
    void closeBox          ()            override {}

    // -- active widgets
    void addButton (const char* label, FAUSTFLOAT* zone) override
    {
        addToggle (label, zone);
    }

    void addCheckButton (const char* label, FAUSTFLOAT* zone) override
    {
        addToggle (label, zone);
    }

    void addVerticalSlider (const char* label, FAUSTFLOAT* zone,
                            FAUSTFLOAT init, FAUSTFLOAT min,
                            FAUSTFLOAT max, FAUSTFLOAT step) override
    {
        addRange (label, zone, init, min, max, step);
    }

    void addHorizontalSlider (const char* label, FAUSTFLOAT* zone,
                              FAUSTFLOAT init, FAUSTFLOAT min,
                              FAUSTFLOAT max, FAUSTFLOAT step) override
    {
        addRange (label, zone, init, min, max, step);
    }

    void addNumEntry (const char* label, FAUSTFLOAT* zone,
                      FAUSTFLOAT init, FAUSTFLOAT min,
                      FAUSTFLOAT max, FAUSTFLOAT step) override
    {
        addRange (label, zone, init, min, max, step);
    }

    // -- passive widgets: nothing in Freaked uses them, and a bargraph is an
    //    output meter rather than something a host should automate
    void addHorizontalBargraph (const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) override {}
    void addVerticalBargraph   (const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) override {}
    void addSoundfile          (const char*, const char*, Soundfile**)            override {}

    /** Turns a Faust label into an identifier a host can store in a session.

        This matches the symbol naming already used by the LV2 ports, so
        "Tail level" stays "Tail_level" on both sides.
    */
    static juce::String makeIdentifier (const juce::String& label)
    {
        juce::String result;

        for (auto character : label)
            result += (juce::CharacterFunctions::isLetterOrDigit (character)
                           ? character
                           : static_cast<juce::juce_wchar> ('_'));

        return result.isEmpty() ? juce::String ("param") : result;
    }

private:
    void addToggle (const char* label, FAUSTFLOAT* zone)
    {
        Entry entry;
        entry.label    = juce::CharPointer_UTF8 (label);
        entry.zone     = zone;
        entry.minValue = 0.0f;
        entry.maxValue = 1.0f;
        entry.step     = 1.0f;
        entry.isToggle = true;
        entries.push_back (entry);
    }

    void addRange (const char* label, FAUSTFLOAT* zone,
                   FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        Entry entry;
        entry.label        = juce::CharPointer_UTF8 (label);
        entry.zone         = zone;
        entry.defaultValue = static_cast<float> (init);
        entry.minValue     = static_cast<float> (min);
        entry.maxValue     = static_cast<float> (max);
        entry.step         = static_cast<float> (step);

        // A degenerate range would make juce::NormalisableRange assert, and a
        // negative or absurd step would too. Both are cheap to defend against.
        if (! (entry.maxValue > entry.minValue))
            entry.maxValue = entry.minValue + 1.0f;

        if (entry.step < 0.0f || entry.step > (entry.maxValue - entry.minValue))
            entry.step = 0.0f;

        entry.defaultValue = juce::jlimit (entry.minValue, entry.maxValue, entry.defaultValue);

        entries.push_back (entry);
    }

    std::vector<Entry> entries;
};
