/*
    Loads a built VST3 through JUCE's own plugin host and exercises it the way
    a DAW would: negotiate a bus layout, prepare, push audio through it, and
    round-trip the state.

    This is deliberately a host level test rather than a unit test. The parts
    most likely to break -- bus negotiation, the channel mapping between the
    host and a fixed channel count Faust DSP, and parameter plumbing -- only
    exist at the boundary the host talks to.

    Usage: FreakedSmokeTest <path to plugin> [more paths...]
*/

#include "FreakedProcessor.h"

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

/** Defined in LegacyGranulatorTest.cpp. */
bool runLegacyGranulatorComparison();

namespace
{
    int failures = 0;

    void check (bool condition, const juce::String& what)
    {
        if (condition)
        {
            std::cout << "    ok   " << what << std::endl;
        }
        else
        {
            std::cout << "    FAIL " << what << std::endl;
            ++failures;
        }
    }

    /** Fills a buffer with a repeatable pseudo random signal. */
    void fillWithNoise (juce::AudioBuffer<float>& buffer, juce::Random& random)
    {
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
                buffer.setSample (channel, sample, random.nextFloat() * 0.5f - 0.25f);
    }

    bool bufferIsFinite (const juce::AudioBuffer<float>& buffer)
    {
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            const auto* data = buffer.getReadPointer (channel);

            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
                if (! std::isfinite (data[sample]))
                    return false;
        }

        return true;
    }

    /** Runs audio through the plugin in one bus layout. */
    void testLayout (juce::AudioPluginInstance& plugin,
                     int inputChannels,
                     int outputChannels,
                     double sampleRate,
                     const juce::String& description)
    {
        juce::AudioProcessor::BusesLayout layout;
        layout.inputBuses.add  (juce::AudioChannelSet::canonicalChannelSet (inputChannels));
        layout.outputBuses.add (juce::AudioChannelSet::canonicalChannelSet (outputChannels));

        if (! plugin.checkBusesLayoutSupported (layout))
        {
            std::cout << "    --   " << description << " (not offered)" << std::endl;
            return;
        }

        check (plugin.setBusesLayout (layout), description + ": layout accepted");

        // A host must never exceed the maximum it announced here, so every
        // block below stays within it.
        constexpr int maximumBlockSize = 1024;
        plugin.prepareToPlay (sampleRate, maximumBlockSize);

        juce::Random random (0x66726b64);
        juce::MidiBuffer midi;

        const int channels = juce::jmax (inputChannels, outputChannels);

        // Any channel, not every channel: these runs are milliseconds long, and
        // Prefreak's first output is the end of a chain of early reflections
        // that can be over a second deep, so it is legitimately still empty
        // here. Per channel output is asserted in testMonoToStereo, which runs
        // long enough for the delay lines to fill.
        bool sawOutput = false;

        // Several blocks, and deliberately not all the same size: hosts vary the
        // block length, and the wrapper chunks internally.
        for (const int blockSize : { maximumBlockSize, 512, 64, 7 })
        {
            juce::AudioBuffer<float> buffer (channels, blockSize);
            buffer.clear();
            fillWithNoise (buffer, random);

            plugin.processBlock (buffer, midi);

            if (! bufferIsFinite (buffer))
            {
                check (false, description + ": output is finite (block " + juce::String (blockSize) + ")");
                plugin.releaseResources();
                return;
            }

            for (int channel = 0; channel < outputChannels; ++channel)
                if (buffer.getMagnitude (channel, 0, blockSize) > 1.0e-6f)
                    sawOutput = true;
        }

        check (true, description + ": output stays finite across varying block sizes");
        check (sawOutput, description + ": produces a non-silent signal");

        plugin.releaseResources();
    }

    /** Checks the loaded plugin offers an editor of a sensible size.

        Actually putting it on screen is done separately, against the processor
        directly: showing a plugin-side editor inside this host would put two
        copies of JUCE on one X11 connection, which is a property of this test
        harness rather than of the plugin.
    */
    void testEditor (juce::AudioPluginInstance& plugin)
    {
        check (plugin.hasEditor(), "reports that it has an editor");

        std::unique_ptr<juce::AudioProcessorEditor> editor (plugin.createEditorIfNeeded());

        if (editor == nullptr)
        {
            check (false, "editor is created");
            return;
        }

        check (true, "editor is created");
        check (editor->getWidth() > 0 && editor->getHeight() > 0,
               "editor has a non-empty size");
    }

    /** Replays auval's render sweep: its sample rates, in its order, with every
        parameter driven to an extreme.

        auval walks the sample rate a long way outside what a DAW normally uses,
        reinitialising between each step, and sets parameters to their limits
        first. Both matter for DSP whose buffer sizes are derived from the
        sample rate, and neither was covered before.
    */
    void testSampleRateSweep (juce::AudioPluginInstance& plugin)
    {
        juce::AudioProcessor::BusesLayout layout;
        layout.inputBuses.add  (juce::AudioChannelSet::stereo());
        layout.outputBuses.add (juce::AudioChannelSet::stereo());

        if (! plugin.checkBusesLayoutSupported (layout) || ! plugin.setBusesLayout (layout))
        {
            std::cout << "    --   sample rate sweep (stereo not offered)" << std::endl;
            return;
        }

        auto* bypassParameter = plugin.getBypassParameter();

        struct Setting { const char* name; float value; };

        juce::Random random (0x67726e6c);
        juce::MidiBuffer midi;

        for (const auto setting : { Setting { "maximum", 1.0f },
                                    Setting { "minimum", 0.0f },
                                    Setting { "default", 0.5f } })
        {
            for (auto* parameter : plugin.getParameters())
                if (parameter != bypassParameter)
                    parameter->setValueNotifyingHost (setting.value);

            // auval's order, which ends by returning to a normal rate.
            for (const auto rate : { 44100.0, 22050.0, 96000.0, 48000.0,
                                     192000.0, 11025.0, 44100.0 })
            {
                for (const int blockSize : { 4096, 512, 137, 64 })
                {
                    plugin.prepareToPlay (rate, blockSize);

                    juce::AudioBuffer<float> buffer (2, blockSize);
                    buffer.clear();
                    fillWithNoise (buffer, random);
                    plugin.processBlock (buffer, midi);

                    if (! bufferIsFinite (buffer))
                    {
                        check (false, "params at " + juce::String (setting.name)
                                        + ", " + juce::String (rate, 0) + " Hz, "
                                        + juce::String (blockSize) + " frames: output is finite");
                        plugin.releaseResources();
                        return;
                    }

                    plugin.releaseResources();
                }
            }

            check (true, juce::String ("sample rate sweep with every parameter at its ")
                             + setting.name);
        }
    }

    /** Checks the effect is actually driven by its input.

        "Not silent" is too weak a test: with a wet/dry control at its default
        the dry path alone keeps the output alive even when the wet side is
        producing nothing at all. This drives the parameters fully wet, then
        compares a run fed noise against a run fed silence. An effect that has
        stopped listening to its input scores the same on both.
    */
    void testRespondsToInput (juce::AudioPluginInstance& plugin)
    {
        juce::AudioProcessor::BusesLayout layout;
        layout.inputBuses.add  (juce::AudioChannelSet::stereo());
        layout.outputBuses.add (juce::AudioChannelSet::stereo());

        if (! plugin.checkBusesLayoutSupported (layout) || ! plugin.setBusesLayout (layout))
        {
            std::cout << "    --   responds to input (stereo not offered)" << std::endl;
            return;
        }

        auto* bypassParameter = plugin.getBypassParameter();

        // Fully wet, so nothing of the input reaches the output except through
        // the effect itself.
        for (auto* parameter : plugin.getParameters())
            if (parameter != bypassParameter)
                parameter->setValueNotifyingHost (1.0f);

        // Deliberately a low sample rate. Delay lines are specified in seconds,
        // and the longest here is ten, so a granulator fed less than that reads
        // buffer it has not recorded into yet and is legitimately near silent.
        // At 11 kHz those ten seconds cost a fifth of the samples they would at
        // 48 kHz, so the test can outrun the delay line cheaply.
        constexpr double sampleRate = 11025.0;
        constexpr int blockSize = 512;
        constexpr int blocks    = 280;      // about thirteen seconds
        constexpr int measured  = 60;       // only the tail is scored

        auto runWith = [&] (bool withInput)
        {
            plugin.prepareToPlay (sampleRate, blockSize);

            juce::Random random (0x66726b64);
            juce::MidiBuffer midi;
            double energy = 0.0;
            long counted = 0;

            for (int block = 0; block < blocks; ++block)
            {
                juce::AudioBuffer<float> buffer (2, blockSize);
                buffer.clear();

                if (withInput)
                    fillWithNoise (buffer, random);

                plugin.processBlock (buffer, midi);

                if (block >= blocks - measured)
                {
                    for (int channel = 0; channel < 2; ++channel)
                    {
                        const auto* data = buffer.getReadPointer (channel);

                        for (int sample = 0; sample < blockSize; ++sample)
                        {
                            energy += double (data[sample]) * data[sample];
                            ++counted;
                        }
                    }
                }
            }

            plugin.releaseResources();
            return counted > 0 ? std::sqrt (energy / double (counted)) : 0.0;
        };

        const auto withInput = runWith (true);
        const auto withSilence = runWith (false);

        std::cout << "    ---- fully wet output: " << withInput
                  << " with input, " << withSilence << " with silence" << std::endl;

        check (withInput > 1.0e-4, "fully wet output is audible when fed a signal");
        check (withInput > withSilence + 1.0e-4, "output actually follows the input");
    }

    /** Feeds a mono source and checks both output channels come alive.

        This is the configuration for putting one of these on a mono track in a
        DAW. A Faust DSP with two inputs gets the single channel fanned out to
        both, so the failure to watch for is an output that stays half silent.
        It runs at a low sample rate and for long enough that the delay lines
        have filled: Prefreak's first output sits behind up to a second and a
        half of early reflections and says nothing before that.
    */
    void testMonoToStereo (juce::AudioPluginInstance& plugin)
    {
        juce::AudioProcessor::BusesLayout layout;
        layout.inputBuses.add  (juce::AudioChannelSet::mono());
        layout.outputBuses.add (juce::AudioChannelSet::stereo());

        if (! plugin.checkBusesLayoutSupported (layout) || ! plugin.setBusesLayout (layout))
        {
            std::cout << "    --   mono to stereo (not offered)" << std::endl;
            return;
        }

        constexpr double sampleRate = 11025.0;
        constexpr int blockSize = 512;
        constexpr int blocks    = 280;
        constexpr int measured  = 60;

        plugin.prepareToPlay (sampleRate, blockSize);

        juce::Random random (0x6d6f6e6f);
        juce::MidiBuffer midi;

        double leftEnergy = 0.0, rightEnergy = 0.0, crossEnergy = 0.0;

        for (int block = 0; block < blocks; ++block)
        {
            juce::AudioBuffer<float> buffer (2, blockSize);
            buffer.clear();

            // One source channel, which is what a mono track provides.
            for (int sample = 0; sample < blockSize; ++sample)
                buffer.setSample (0, sample, random.nextFloat() * 0.5f - 0.25f);

            plugin.processBlock (buffer, midi);

            if (block < blocks - measured)
                continue;

            const auto* left  = buffer.getReadPointer (0);
            const auto* right = buffer.getReadPointer (1);

            for (int sample = 0; sample < blockSize; ++sample)
            {
                leftEnergy  += double (left[sample])  * left[sample];
                rightEnergy += double (right[sample]) * right[sample];
                crossEnergy += double (left[sample])  * right[sample];
            }
        }

        plugin.releaseResources();

        const auto leftRms  = std::sqrt (leftEnergy  / (blockSize * double (measured)));
        const auto rightRms = std::sqrt (rightEnergy / (blockSize * double (measured)));
        const auto correlation = (leftEnergy > 0.0 && rightEnergy > 0.0)
                                   ? crossEnergy / std::sqrt (leftEnergy * rightEnergy)
                                   : 1.0;

        std::cout << "    ---- mono in: left " << leftRms << ", right " << rightRms
                  << ", L/R correlation " << correlation
                  << (correlation < 0.9 ? "  (decorrelated)" : "  (centred)") << std::endl;

        check (leftRms > 1.0e-4 && rightRms > 1.0e-4,
               "mono to stereo: both output channels carry signal");
    }

    void testPlugin (juce::AudioPluginFormatManager& formatManager, const juce::File& file)
    {
        std::cout << "\n" << file.getFileName() << std::endl;

        juce::OwnedArray<juce::PluginDescription> descriptions;

        for (auto* format : formatManager.getFormats())
            if (format->fileMightContainThisPluginType (file.getFullPathName()))
                format->findAllTypesForFile (descriptions, file.getFullPathName());

        if (descriptions.isEmpty())
        {
            check (false, "plugin was discovered by the host");
            return;
        }

        check (true, "plugin was discovered by the host");

        juce::String error;
        auto plugin = formatManager.createPluginInstance (*descriptions[0], 48000.0, 512, error);

        if (plugin == nullptr)
        {
            check (false, "plugin instantiates (" + error + ")");
            return;
        }

        check (true, "plugin instantiates");

        const auto& parameters = plugin->getParameters();
        check (! parameters.isEmpty(), "exposes parameters to the host");

        std::cout << "    ---- " << parameters.size() << " parameters: ";
        for (auto* parameter : parameters)
            std::cout << parameter->getName (32) << "  ";
        std::cout << std::endl;

        // Every parameter has to survive a state round trip, which is what a
        // session recall in the DAW relies on. Bypass is excluded: it is
        // synthesised by the VST3 wrapper and owned by the host, not by the
        // plugin's own state.
        auto* bypassParameter = plugin->getBypassParameter();

        auto isPersisted = [bypassParameter] (const juce::AudioProcessorParameter* parameter)
        {
            return parameter != bypassParameter;
        };

        for (auto* parameter : parameters)
            if (isPersisted (parameter))
                parameter->setValueNotifyingHost (0.75f);

        // Compare the real values rather than the normalised ones. A stepped
        // parameter snaps when it is denormalised, so a saved 7.7 comes back as
        // a slightly different normalised number that denormalises to the same
        // 7.7. The audible state is what has to survive, not its encoding.
        std::map<const juce::AudioProcessorParameter*, juce::String> expected;

        for (auto* parameter : parameters)
            if (isPersisted (parameter))
                expected[parameter] = parameter->getCurrentValueAsText();

        juce::MemoryBlock state;
        plugin->getStateInformation (state);
        check (state.getSize() > 0, "produces a non-empty state blob");

        for (auto* parameter : parameters)
            if (isPersisted (parameter))
                parameter->setValueNotifyingHost (0.1f);

        plugin->setStateInformation (state.getData(), static_cast<int> (state.getSize()));

        bool restored = true;
        for (auto* parameter : parameters)
        {
            if (! isPersisted (parameter))
                continue;

            const auto target = expected[parameter];
            const auto actual = parameter->getCurrentValueAsText();

            if (actual != target)
            {
                restored = false;
                std::cout << "    ---- '" << parameter->getName (32)
                          << "' came back as " << actual
                          << " instead of " << target << std::endl;
            }
        }

        check (restored, "state round trip restores every parameter");

        testEditor (*plugin);
        testRespondsToInput (*plugin);
        testMonoToStereo (*plugin);
        testSampleRateSweep (*plugin);

        for (const double sampleRate : { 44100.0, 48000.0, 96000.0 })
        {
            testLayout (*plugin, 2, 2, sampleRate, "stereo in/out @ " + juce::String (sampleRate, 0));
            testLayout (*plugin, 1, 1, sampleRate, "mono in/out @ " + juce::String (sampleRate, 0));
            testLayout (*plugin, 1, 2, sampleRate, "mono to stereo @ " + juce::String (sampleRate, 0));
        }
    }
}

namespace
{
    /** Returns true when the image contains more than a single flat colour. */
    bool imageHasContent (const juce::Image& image)
    {
        const auto reference = image.getPixelAt (0, 0);

        for (int y = 0; y < image.getHeight(); y += 2)
            for (int x = 0; x < image.getWidth(); x += 2)
                if (image.getPixelAt (x, y) != reference)
                    return true;

        return false;
    }

    /** Builds the wrapper's own editor and renders it off screen.

        This links the processor directly rather than going through a plugin
        format, so the editor exercised here is the one in Plugins/Source.
        Rendering into an image rather than onto the desktop runs the same
        resized() and paint() code a host would trigger, but needs no display,
        so it behaves the same on all three CI platforms.
    */
    void testEditorRendering()
    {
        std::cout << "\nEditor (" << FREAKED_PLUGIN_NAME << ", built directly)" << std::endl;

        FreakedAudioProcessor processor;

        std::unique_ptr<juce::AudioProcessorEditor> editor (processor.createEditor());
        check (editor != nullptr, "editor is created");

        if (editor == nullptr)
            return;

        check (editor->getWidth() > 0 && editor->getHeight() > 0,
               "editor has a non-empty size");

        auto render = [&editor] (const juce::String& what)
        {
            juce::Image image (juce::Image::ARGB,
                               juce::jmax (1, editor->getWidth()),
                               juce::jmax (1, editor->getHeight()),
                               true);
            {
                juce::Graphics g (image);
                editor->paintEntireComponent (g, true);
            }

            check (imageHasContent (image), what);
        };

        render ("editor draws something at its default size");

        // Awkward sizes exercise the grid layout, including a part-filled row.
        const auto width  = editor->getWidth();
        const auto height = editor->getHeight();

        for (const auto scale : { 1.4, 0.6, 2.0 })
        {
            editor->setSize (juce::roundToInt (width  * scale),
                             juce::roundToInt (height * scale));
            render ("editor draws at " + juce::String (scale, 1) + "x its default size");
        }

        editor->setSize (width, height);

        // A parameter change has to reach the attached slider.
        if (auto* parameter = processor.getParameterAt (0))
        {
            parameter->setValueNotifyingHost (0.42f);
            juce::MessageManager::getInstance()->runDispatchLoopUntil (50);
            render ("editor still draws after a parameter change");
        }
    }
}

int main (int argc, char** argv)
{
    juce::ScopedJuceInitialiser_GUI juceInitialiser;

    if (argc < 2)
    {
        std::cerr << "usage: FreakedSmokeTest <plugin> [plugin...]" << std::endl;
        return 2;
    }

    // JUCE 8 requires the host to opt into each format explicitly.
    juce::AudioPluginFormatManager formatManager;
    formatManager.addFormat (new juce::VST3PluginFormat());

   #if JUCE_PLUGINHOST_AU && JUCE_MAC
    formatManager.addFormat (new juce::AudioUnitPluginFormat());
   #endif

    for (int i = 1; i < argc; ++i)
    {
        // Resolve relative paths so the test can be invoked from the build tree.
        const auto file = juce::File::getCurrentWorkingDirectory()
                              .getChildFile (juce::String (juce::CharPointer_UTF8 (argv[i])));

        if (! file.exists())
        {
            std::cerr << "no such plugin: " << file.getFullPathName() << std::endl;
            ++failures;
            continue;
        }

        testPlugin (formatManager, file);
    }

    testEditorRendering();

    if (! runLegacyGranulatorComparison())
    {
        std::cout << "    FAIL Granulator no longer matches the LV2 reference build" << std::endl;
        ++failures;
    }
    else
    {
        std::cout << "    ok   Granulator still matches the LV2 reference build" << std::endl;
    }

    std::cout << std::endl
              << (failures == 0 ? "All checks passed."
                                : juce::String (failures) + " check(s) FAILED.")
              << std::endl;

    return failures == 0 ? 0 : 1;
}
