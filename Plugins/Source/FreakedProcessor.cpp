#include "FreakedProcessor.h"
#include "FreakedEditor.h"
#include "FaustFactory.h"

#include <faust/dsp/dsp.h>

namespace
{
    /** The largest block the DSP is asked to process in one go.

        Some hosts hand over more samples than they announced in
        prepareToPlay, so processBlock walks the buffer in chunks of at most
        this size rather than trusting the announced maximum.
    */
    constexpr int maxChunkSize = 4096;

    /** Only mono and stereo are offered. Anything wider would need a channel
        mapping the Faust sources do not describe.
    */
    constexpr int maxHostChannels = 2;
}

juce::AudioProcessor::BusesProperties FreakedAudioProcessor::createBusesProperties()
{
    return BusesProperties()
             .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
             .withOutput ("Output", juce::AudioChannelSet::stereo(), true);
}

FreakedAudioProcessor::FreakedAudioProcessor()
    : juce::AudioProcessor (createBusesProperties())
{
    // The first instance doubles as the probe used to discover the DSP's
    // parameters and channel counts.
    auto probe = createFreakedDsp();
    jassert (probe != nullptr);

    dspNumInputs  = probe->getNumInputs();
    dspNumOutputs = probe->getNumOutputs();

    probe->init (static_cast<int> (currentSampleRate));

    FaustParameterCollector collector;
    probe->buildUserInterface (&collector);

    for (const auto& entry : collector.getEntries())
    {
        FaustParameter parameter;
        parameter.label        = entry.label;
        parameter.id           = FaustParameterCollector::makeIdentifier (entry.label);
        parameter.defaultValue = entry.defaultValue;
        parameter.minValue     = entry.minValue;
        parameter.maxValue     = entry.maxValue;
        parameter.step         = entry.step;
        parameter.isToggle     = entry.isToggle;
        parameters.push_back (std::move (parameter));
    }

    for (const auto& parameter : parameters)
    {
        juce::NormalisableRange<float> range (parameter.minValue, parameter.maxValue);
        range.interval = parameter.step;

        auto* juceParameter = new juce::AudioParameterFloat (
            juce::ParameterID { parameter.id, 1 },
            parameter.label,
            range,
            parameter.defaultValue);

        juceParameters.push_back (juceParameter);
        addParameter (juceParameter);
    }

    instances.push_back (std::move (probe));
    rebuildInstances (1, currentSampleRate);
}

FreakedAudioProcessor::~FreakedAudioProcessor() = default;

void FreakedAudioProcessor::rebuildInstances (int instanceCount, double sampleRate)
{
    instanceCount = juce::jmax (1, instanceCount);

    while (static_cast<int> (instances.size()) > instanceCount)
        instances.pop_back();

    while (static_cast<int> (instances.size()) < instanceCount)
        instances.push_back (createFreakedDsp());

    for (auto& instance : instances)
        instance->init (static_cast<int> (sampleRate));

    // Re-point every parameter at the zones of the instances that exist now,
    // then push the current values back in: init() resets the DSP to the Faust
    // defaults, which would otherwise discard whatever the host had set.
    for (auto& parameter : parameters)
        parameter.zones.clear();

    for (auto& instance : instances)
    {
        FaustParameterCollector collector;
        instance->buildUserInterface (&collector);

        const auto& entries = collector.getEntries();
        jassert (entries.size() == parameters.size());

        const auto count = juce::jmin (entries.size(), parameters.size());

        for (size_t i = 0; i < count; ++i)
            parameters[i].zones.push_back (entries[i].zone);
    }

    for (size_t i = 0; i < parameters.size(); ++i)
        for (auto* zone : parameters[i].zones)
            *zone = static_cast<FAUSTFLOAT> (juceParameters[i]->get());

    inputPointers.assign (static_cast<size_t> (instanceCount * juce::jmax (1, dspNumInputs)), nullptr);
    outputPointers.assign (static_cast<size_t> (instanceCount * juce::jmax (1, dspNumOutputs)), nullptr);
}

void FreakedAudioProcessor::prepareToPlay (double sampleRate, int maximumExpectedSamplesPerBlock)
{
    currentSampleRate = sampleRate > 0.0 ? sampleRate : 44100.0;

    const int outputChannels = juce::jmax (1, getTotalNumOutputChannels());
    const int instanceCount  = dspNumOutputs > 0 ? juce::jmax (1, outputChannels / dspNumOutputs)
                                                 : 1;

    rebuildInstances (instanceCount, currentSampleRate);

    const int chunk = juce::jlimit (1, maxChunkSize,
                                    juce::jmax (maximumExpectedSamplesPerBlock, 1));

    inputScratch.setSize (juce::jmax (1, instanceCount * dspNumInputs), chunk, false, true, true);
    inputScratch.clear();
}

void FreakedAudioProcessor::releaseResources()
{
    inputScratch.setSize (0, 0);
}

bool FreakedAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const auto& mainOutput = layouts.getMainOutputChannelSet();
    const auto& mainInput  = layouts.getMainInputChannelSet();

    if (mainOutput.isDisabled())
        return false;

    // Discrete or ambisonic sets carry no meaning for these effects.
    if (mainOutput != juce::AudioChannelSet::mono()
        && mainOutput != juce::AudioChannelSet::stereo())
        return false;

    if (! mainInput.isDisabled()
        && mainInput != juce::AudioChannelSet::mono()
        && mainInput != juce::AudioChannelSet::stereo())
        return false;

    const int outputChannels = mainOutput.size();
    const int inputChannels  = mainInput.size();

    if (outputChannels > maxHostChannels || outputChannels < 1)
        return false;

    // The instances have to tile the output exactly.
    if (dspNumOutputs <= 0 || outputChannels % dspNumOutputs != 0)
        return false;

    const int instanceCount = outputChannels / dspNumOutputs;
    const int requiredInputs = instanceCount * dspNumInputs;

    // Either the host provides exactly what the instances consume, or it
    // provides a single channel which is fanned out to all of them.
    return inputChannels == requiredInputs || inputChannels == 1;
}

void FreakedAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    const int numSamples         = buffer.getNumSamples();
    const int totalInputChannels = getTotalNumInputChannels();
    const int totalOutputChannels = getTotalNumOutputChannels();
    const int instanceCount      = static_cast<int> (instances.size());

    // Anything the layout negotiation did not account for is silenced rather
    // than left holding whatever the host passed in.
    for (int channel = totalOutputChannels; channel < buffer.getNumChannels(); ++channel)
        buffer.clear (channel, 0, numSamples);

    if (instanceCount == 0 || numSamples <= 0)
        return;

    if (instanceCount * dspNumOutputs > totalOutputChannels
        || inputScratch.getNumSamples() <= 0)
    {
        buffer.clear();
        return;
    }

    // Push the host's parameter values into every instance's zones.
    for (size_t i = 0; i < parameters.size(); ++i)
    {
        const auto value = static_cast<FAUSTFLOAT> (juceParameters[i]->get());

        for (auto* zone : parameters[i].zones)
            *zone = value;
    }

    const int chunkSize = inputScratch.getNumSamples();

    for (int offset = 0; offset < numSamples; offset += chunkSize)
    {
        const int samplesThisTime = juce::jmin (chunkSize, numSamples - offset);

        for (int instance = 0; instance < instanceCount; ++instance)
        {
            for (int channel = 0; channel < dspNumInputs; ++channel)
            {
                const int scratchChannel = instance * dspNumInputs + channel;

                if (totalInputChannels > 0)
                {
                    // With a single input channel every DSP input reads from it,
                    // which is what turns a mono source into a stereo effect.
                    const int sourceChannel = juce::jmin (scratchChannel, totalInputChannels - 1);

                    inputScratch.copyFrom (scratchChannel, 0, buffer, sourceChannel,
                                           offset, samplesThisTime);
                }
                else
                {
                    inputScratch.clear (scratchChannel, 0, samplesThisTime);
                }

                inputPointers[static_cast<size_t> (scratchChannel)]
                    = inputScratch.getWritePointer (scratchChannel);
            }

            for (int channel = 0; channel < dspNumOutputs; ++channel)
            {
                const int bufferChannel = instance * dspNumOutputs + channel;

                outputPointers[static_cast<size_t> (bufferChannel)]
                    = buffer.getWritePointer (bufferChannel) + offset;
            }

            instances[static_cast<size_t> (instance)]->compute (
                samplesThisTime,
                inputPointers.data() + static_cast<size_t> (instance * dspNumInputs),
                outputPointers.data() + static_cast<size_t> (instance * dspNumOutputs));
        }
    }
}

juce::AudioProcessorEditor* FreakedAudioProcessor::createEditor()
{
    return new FreakedEditor (*this);
}

void FreakedAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::XmlElement state ("FreakedState");
    state.setAttribute ("plugin", FREAKED_PLUGIN_NAME);
    state.setAttribute ("version", 1);

    for (size_t i = 0; i < parameters.size(); ++i)
        state.setAttribute (parameters[i].id, static_cast<double> (juceParameters[i]->get()));

    copyXmlToBinary (state, destData);
}

void FreakedAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    auto state = getXmlFromBinary (data, sizeInBytes);

    if (state == nullptr || ! state->hasTagName ("FreakedState"))
        return;

    for (size_t i = 0; i < parameters.size(); ++i)
    {
        if (! state->hasAttribute (parameters[i].id))
            continue;

        const auto stored = static_cast<float> (
            state->getDoubleAttribute (parameters[i].id,
                                       static_cast<double> (parameters[i].defaultValue)));

        auto* parameter = juceParameters[i];
        parameter->setValueNotifyingHost (parameter->convertTo0to1 (stored));
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FreakedAudioProcessor();
}
