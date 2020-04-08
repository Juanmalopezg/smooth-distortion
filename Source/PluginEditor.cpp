/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HolaMundoAudioProcessorEditor::HolaMundoAudioProcessorEditor(HolaMundoAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p)
{
	addAndMakeVisible(driveKnob = new Slider("Drive"));
	driveKnob->setLookAndFeel(&lookAndFeel);
	driveKnob->setSliderStyle(Slider::Rotary);
	driveKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);

	addAndMakeVisible(rangeKnob = new Slider("Range"));
	rangeKnob->setLookAndFeel(&lookAndFeel);
	rangeKnob->setSliderStyle(Slider::Rotary);
	rangeKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);

	addAndMakeVisible(blendKnob = new Slider("Blend"));
	blendKnob->setLookAndFeel(&lookAndFeel);
	blendKnob->setSliderStyle(Slider::Rotary);
	blendKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);

	addAndMakeVisible(volumeKnob = new Slider("Volume"));
	volumeKnob->setLookAndFeel(&lookAndFeel);
	volumeKnob->setSliderStyle(Slider::Rotary);
	volumeKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);

	driveAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "drive", *driveKnob);
	rangeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "range", *rangeKnob);
	blendAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "blend", *blendKnob);
	volumeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "volume", *volumeKnob);

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(600, 300);
}

HolaMundoAudioProcessorEditor::~HolaMundoAudioProcessorEditor()
{
	driveKnob->setLookAndFeel(nullptr);
	rangeKnob->setLookAndFeel(nullptr);
	blendKnob->setLookAndFeel(nullptr);
	volumeKnob->setLookAndFeel(nullptr);
}

//==============================================================================
void HolaMundoAudioProcessorEditor::paint(Graphics& g)
{

	// (Our component is opaque, so we must completely fill the background with a solid colour)
	//g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
	g.fillAll(Colour(14, 24, 33));
	svgDistor = Drawable::createFromImageData(BinaryData::juanma_recurso_texto_svg, BinaryData::juanma_recurso_texto_svgSize);
	addAndMakeVisible(*svgDistor);
	svgDistor->setBounds(30, 175,getWidth(),getHeight());

}

void HolaMundoAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..

	driveKnob->setBounds(((getWidth() / 6) * 1) + (20 * 1) - 50, (getHeight() - 175) - (100 / 2), 100, 100);
	rangeKnob->setBounds(((getWidth() / 6) * 2) + (20 * 2) - 50, (getHeight() - 175) - (100 / 2), 100, 100);
	blendKnob->setBounds(((getWidth() / 6) * 3) + (20 * 3) - 50, (getHeight() - 175) - (100 / 2), 100, 100);
	volumeKnob->setBounds(((getWidth() / 6) * 4) + (20 * 4) - 50, (getHeight() - 175) - (100 / 2), 100, 100);

}
