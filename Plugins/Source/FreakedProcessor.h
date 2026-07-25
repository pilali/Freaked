#pragma once

#include "FaustParameters.h"
#include "FreakedPluginConfig.h"

#include <juce_audio_processors/juce_audio_processors.h>

#include <memory>
#include <vector>

class dsp;

/**
    Hosts a Faust DSP inside an AU / VST3 plugin.

    The processor is entirely driven by whatever the DSP declares: the
    parameters, their ranges and the channel counts all come from the generated
    Faust class, so all five Freaked plugins share this one implementation.

    A Faust DSP has a fixed channel count. When the host asks for more channels
    than the DSP provides (a mono DSP on a stereo track), several instances are
    run side by side and fed the same parameter values.
*/
class FreakedAudioProcessor final : public juce::AudioProcessor
{
public:
    FreakedAudioProcessor();
    ~FreakedAudioProcessor() override;

    void prepareToPlay (double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void releaseResources() override;
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override                            { return true; }

    const juce::String getName() const override                { return FREAKED_PLUGIN_NAME; }
    bool acceptsMidi() const override                          { return false; }
    bool producesMidi() const override                         { return false; }
    bool isMidiEffect() const override                         { return false; }
    double getTailLengthSeconds() const override               { return FREAKED_TAIL_SECONDS; }

    int getNumPrograms() override                              { return 1; }
    int getCurrentProgram() override                           { return 0; }
    void setCurrentProgram (int) override                      {}
    const juce::String getProgramName (int) override           { return "Default"; }
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    /** The controls the DSP declared, in the order Faust reported them. */
    const std::vector<FaustParameter>& getFaustParameters() const noexcept { return parameters; }

    /** The host facing parameter backing the n-th Faust control. */
    juce::AudioParameterFloat* getParameterAt (int index) const noexcept
    {
        return juceParameters[static_cast<size_t> (index)];
    }

private:
    /** The bus layout the plugin advertises before the host negotiates.

        BusesProperties is protected in AudioProcessor, so this has to be a
        member rather than a free function.
    */
    static BusesProperties createBusesProperties();

    /** Rebuilds the DSP instances and re-points every parameter at their zones. */
    void rebuildInstances (int instanceCount, double sampleRate);

    std::vector<std::unique_ptr<dsp>> instances;
    std::vector<FaustParameter> parameters;
    std::vector<juce::AudioParameterFloat*> juceParameters;

    int dspNumInputs  = 0;
    int dspNumOutputs = 0;

    double currentSampleRate = 44100.0;

    // Faust is not required to tolerate reading and writing the same memory, and
    // JUCE hands out a single buffer for input and output. The input is copied
    // here first so the DSP always sees distinct pointers.
    juce::AudioBuffer<float> inputScratch;

    // Scratch pointer arrays, sized once so processBlock never allocates.
    std::vector<FAUSTFLOAT*> inputPointers;
    std::vector<FAUSTFLOAT*> outputPointers;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreakedAudioProcessor)
};
