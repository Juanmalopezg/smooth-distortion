#pragma once

#include "PluginProcessor.h"
#include "KnobStyle.h"

#include <JuceHeader.h>

//==============================================================================
class DistortionPluginAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    DistortionPluginAudioProcessorEditor(DistortionPluginAudioProcessor &);

    ~DistortionPluginAudioProcessorEditor();

    //==============================================================================
    void paint(juce::Graphics &) override;

    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    juce::Slider driveKnob, rangeKnob, blendKnob, volumeKnob;
    juce::AudioProcessorValueTreeState::SliderAttachment driveAttachment, rangeAttachment, blendAttachment, volumeAttachment;
    DistortionPluginAudioProcessor &processorRef;
    KnobStyle lookAndFeel;
    std::unique_ptr <juce::Drawable> svgDistor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionPluginAudioProcessorEditor)

};
