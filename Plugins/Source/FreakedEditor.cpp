#include "FreakedEditor.h"
#include "FreakedProcessor.h"

namespace
{
    constexpr int headerHeight = 46;
    constexpr int padding      = 16;
    constexpr int cellWidth    = 104;
    constexpr int cellHeight   = 126;

    const juce::Colour backgroundColour { 0xff1c1e1a };
    const juce::Colour panelColour      { 0xff26291f };
    const juce::Colour accentColour     { 0xffa8d60c };
    const juce::Colour textColour       { 0xffe6e8dc };
    const juce::Colour dimTextColour    { 0xff8b8f7e };
}

FreakedLookAndFeel::FreakedLookAndFeel()
{
    setColour (juce::Slider::textBoxTextColourId,      textColour);
    setColour (juce::Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
    setColour (juce::Slider::textBoxOutlineColourId,   juce::Colours::transparentBlack);
    setColour (juce::Slider::textBoxHighlightColourId, accentColour.withAlpha (0.3f));
    setColour (juce::Label::textColourId,              dimTextColour);
}

void FreakedLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                                           float sliderPosProportional, float rotaryStartAngle,
                                           float rotaryEndAngle, juce::Slider&)
{
    const auto bounds = juce::Rectangle<int> (x, y, width, height).toFloat().reduced (4.0f);
    const auto radius = juce::jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    const auto centre = bounds.getCentre();
    const auto angle  = rotaryStartAngle
                      + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    const auto lineWidth = juce::jmax (2.0f, radius * 0.14f);
    const auto arcRadius = radius - lineWidth * 0.5f;

    juce::Path background;
    background.addCentredArc (centre.x, centre.y, arcRadius, arcRadius, 0.0f,
                              rotaryStartAngle, rotaryEndAngle, true);
    g.setColour (panelColour.brighter (0.25f));
    g.strokePath (background, juce::PathStrokeType (lineWidth, juce::PathStrokeType::curved,
                                                    juce::PathStrokeType::rounded));

    if (sliderPosProportional > 0.0f)
    {
        juce::Path value;
        value.addCentredArc (centre.x, centre.y, arcRadius, arcRadius, 0.0f,
                             rotaryStartAngle, angle, true);
        g.setColour (accentColour);
        g.strokePath (value, juce::PathStrokeType (lineWidth, juce::PathStrokeType::curved,
                                                   juce::PathStrokeType::rounded));
    }

    // The knob body and its pointer.
    const auto bodyRadius = arcRadius - lineWidth * 1.1f;
    g.setColour (panelColour.brighter (0.1f));
    g.fillEllipse (juce::Rectangle<float> (bodyRadius * 2.0f, bodyRadius * 2.0f)
                       .withCentre (centre));

    juce::Path pointer;
    const auto pointerThickness = juce::jmax (2.0f, bodyRadius * 0.12f);
    pointer.addRoundedRectangle (-pointerThickness * 0.5f, -bodyRadius * 0.92f,
                                 pointerThickness, bodyRadius * 0.5f,
                                 pointerThickness * 0.5f);
    pointer.applyTransform (juce::AffineTransform::rotation (angle).translated (centre));
    g.setColour (textColour);
    g.fillPath (pointer);
}

FreakedEditor::FreakedEditor (FreakedAudioProcessor& processorToUse)
    : juce::AudioProcessorEditor (&processorToUse),
      processor (processorToUse)
{
    setLookAndFeel (&lookAndFeel);

    const auto& faustParameters = processor.getFaustParameters();
    const int parameterCount = static_cast<int> (faustParameters.size());

    for (int i = 0; i < parameterCount; ++i)
    {
        auto knob = std::make_unique<Knob>();

        knob->slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
        knob->slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 88, 18);
        knob->slider.setRotaryParameters (juce::MathConstants<float>::pi * 1.2f,
                                          juce::MathConstants<float>::pi * 2.8f,
                                          true);
        knob->slider.setDoubleClickReturnValue (true, faustParameters[static_cast<size_t> (i)].defaultValue);

        knob->label.setText (faustParameters[static_cast<size_t> (i)].label,
                             juce::dontSendNotification);
        knob->label.setJustificationType (juce::Justification::centred);
        knob->label.setInterceptsMouseClicks (false, false);
        knob->label.setFont (juce::FontOptions (12.0f));

        // The attachment owns the two-way link with the host, so automation and
        // the knob can never drift apart.
        knob->attachment = std::make_unique<juce::SliderParameterAttachment> (
            *processor.getParameterAt (i), knob->slider, nullptr);

        addAndMakeVisible (knob->slider);
        addAndMakeVisible (knob->label);
        knobs.push_back (std::move (knob));
    }

    columns = parameterCount <= 4 ? juce::jmax (1, parameterCount) : 3;
    rows    = juce::jmax (1, (parameterCount + columns - 1) / columns);

    setSize (padding * 2 + columns * cellWidth,
             headerHeight + rows * cellHeight + padding);
}

FreakedEditor::~FreakedEditor()
{
    // The attachments reference the sliders, so they must go before the
    // look and feel this editor installed is torn down.
    knobs.clear();
    setLookAndFeel (nullptr);
}

void FreakedEditor::paint (juce::Graphics& g)
{
    g.fillAll (backgroundColour);

    auto header = getLocalBounds().removeFromTop (headerHeight);

    g.setColour (panelColour);
    g.fillRect (header);
    g.setColour (accentColour);
    g.fillRect (header.removeFromBottom (2));

    auto textArea = header.reduced (padding, 0);

    g.setColour (textColour);
    g.setFont (juce::FontOptions (17.0f, juce::Font::bold));
    g.drawText (FREAKED_PLUGIN_NAME, textArea, juce::Justification::centredLeft, true);

    g.setColour (dimTextColour);
    g.setFont (juce::FontOptions (11.0f));
    g.drawText ("FREAKED", textArea, juce::Justification::centredRight, true);
}

void FreakedEditor::resized()
{
    auto content = getLocalBounds();
    content.removeFromTop (headerHeight);
    content = content.reduced (padding, 0);

    const int knobCount = static_cast<int> (knobs.size());

    for (int i = 0; i < knobCount; ++i)
    {
        const int row    = i / columns;
        const int column = i % columns;

        // The last row is centred when it does not fill the grid.
        const int itemsInRow = juce::jmin (columns, knobCount - row * columns);
        const int rowWidth   = itemsInRow * cellWidth;
        const int rowLeft    = content.getX() + (content.getWidth() - rowWidth) / 2;

        juce::Rectangle<int> cell (rowLeft + column * cellWidth,
                                   content.getY() + row * cellHeight,
                                   cellWidth,
                                   cellHeight);

        auto& knob = *knobs[static_cast<size_t> (i)];
        knob.label.setBounds (cell.removeFromTop (20));
        knob.slider.setBounds (cell.reduced (4, 0));
    }
}
