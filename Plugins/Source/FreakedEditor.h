#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include <memory>
#include <vector>

class FreakedAudioProcessor;

/** Rotary styling shared by every Freaked plugin. */
class FreakedLookAndFeel final : public juce::LookAndFeel_V4
{
public:
    FreakedLookAndFeel();

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle,
                           float rotaryEndAngle, juce::Slider& slider) override;
};

/**
    A control panel built from whatever the Faust DSP declared.

    Nothing here is plugin specific: the knobs, their ranges and the window size
    all follow from the parameter list the processor discovered.
*/
class FreakedEditor final : public juce::AudioProcessorEditor
{
public:
    explicit FreakedEditor (FreakedAudioProcessor& processorToUse);
    ~FreakedEditor() override;

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    struct Knob
    {
        juce::Slider slider;
        juce::Label  label;
        std::unique_ptr<juce::SliderParameterAttachment> attachment;
    };

    FreakedAudioProcessor& processor;
    FreakedLookAndFeel lookAndFeel;
    std::vector<std::unique_ptr<Knob>> knobs;

    int columns = 1;
    int rows    = 1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreakedEditor)
};
