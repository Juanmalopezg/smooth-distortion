#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionPluginAudioProcessorEditor::DistortionPluginAudioProcessorEditor(DistortionPluginAudioProcessor &p)
        : AudioProcessorEditor(&p), processorRef(p), driveAttachment(p.state, "drive", driveKnob),
          rangeAttachment(p.state, "range", rangeKnob),
          blendAttachment(p.state, "blend", blendKnob),
          volumeAttachment(p.state, "volume", volumeKnob) {

    for (auto *slider: {&driveKnob, &rangeKnob, &blendKnob, &volumeKnob}) {

        slider->setLookAndFeel(&lookAndFeel);
        slider->setSliderStyle(juce::Slider::Rotary);
        slider->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);

        addAndMakeVisible(slider);

    }
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(600, 300);
}

DistortionPluginAudioProcessorEditor::~DistortionPluginAudioProcessorEditor() {
    driveKnob.setLookAndFeel(nullptr);
    rangeKnob.setLookAndFeel(nullptr);
    blendKnob.setLookAndFeel(nullptr);
    volumeKnob.setLookAndFeel(nullptr);
}

//==============================================================================
void DistortionPluginAudioProcessorEditor::paint(juce::Graphics &g) {
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colour(14, 24, 33));
    svgDistor = juce::Drawable::createFromImageData(BinaryData::background_svg,BinaryData::background_svgSize);

    addAndMakeVisible(*svgDistor);
    svgDistor->setBounds(30, 175, getWidth(), getHeight());
}

void DistortionPluginAudioProcessorEditor::resized() {
    driveKnob.setBounds(((getWidth() / 6) * 1) + (20 * 1) - 50, (getHeight() - 175) - (100 / 2), 100, 100);
    rangeKnob.setBounds(((getWidth() / 6) * 2) + (20 * 2) - 50, (getHeight() - 175) - (100 / 2), 100, 100);
    blendKnob.setBounds(((getWidth() / 6) * 3) + (20 * 3) - 50, (getHeight() - 175) - (100 / 2), 100, 100);
    volumeKnob.setBounds(((getWidth() / 6) * 4) + (20 * 4) - 50, (getHeight() - 175) - (100 / 2), 100, 100);
}
