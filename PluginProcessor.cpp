#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionPluginAudioProcessor::DistortionPluginAudioProcessor()
        : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                                 .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                                 .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
), state(*this, nullptr, "STATE", {
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"drive", 1}, "Drive", 0.0f, 1.f, 1.f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"range", 1}, "Range", 0.0f, 3000.0f, 1.f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"blend", 1}, "Blend", 0.0f, 1.f, 1.f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"volume", 1}, "Volume", 0.0f, 3.f, 1.f)
}) {
}

//==============================================================================
const juce::String DistortionPluginAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool DistortionPluginAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool DistortionPluginAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool DistortionPluginAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double DistortionPluginAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int DistortionPluginAudioProcessor::getNumPrograms() {
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int DistortionPluginAudioProcessor::getCurrentProgram() {
    return 0;
}

void DistortionPluginAudioProcessor::setCurrentProgram(int index) {
    juce::ignoreUnused(index);
}

const juce::String DistortionPluginAudioProcessor::getProgramName(int index) {
    juce::ignoreUnused(index);
    return {};
}

void DistortionPluginAudioProcessor::changeProgramName(int index, const juce::String &newName) {
    juce::ignoreUnused(index, newName);
}

//==============================================================================
void DistortionPluginAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused(sampleRate, samplesPerBlock);
}

void DistortionPluginAudioProcessor::releaseResources() {
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool DistortionPluginAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const {
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}

void DistortionPluginAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                                  juce::MidiBuffer &midiMessages) {

    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    float drive = *state.getRawParameterValue("drive");
    float range = *state.getRawParameterValue("range");
    float blend = *state.getRawParameterValue("blend");
    float volume = *state.getRawParameterValue("volume");


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int sample = 0;sample < buffer.getNumSamples(); sample++) {

            float cleanSig = *channelData;

            *channelData *= drive*range;

            *channelData = (((((2.f / float_Pi) * atan(*channelData)) * blend)+(cleanSig*(1.f-blend)))/2.f) * volume;

            channelData++;
        }
    }
}

//==============================================================================
bool DistortionPluginAudioProcessor::hasEditor() const {
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *DistortionPluginAudioProcessor::createEditor() {
    return new DistortionPluginAudioProcessorEditor(*this);
}

//==============================================================================
void DistortionPluginAudioProcessor::getStateInformation(juce::MemoryBlock &destData) {
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    if (auto xmlState = state.copyState().createXml())
        copyXmlToBinary(*xmlState, destData);
}

void DistortionPluginAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    if (auto xmlState = getXmlFromBinary(data, sizeInBytes))
        state.replaceState(juce::ValueTree::fromXml(*xmlState));
}

DistortionPluginAudioProcessor::~DistortionPluginAudioProcessor() {

}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE

createPluginFilter() {
    return new DistortionPluginAudioProcessor();
}
