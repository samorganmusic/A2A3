/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Try2AudioProcessor::Try2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters(*this, nullptr, Identifier("MODUNA"),
                              {
                           std::make_unique<AudioParameterFloat>(
                                                                 "gain",
                                                                 "Gain",
                                                                 0.0f,
                                                                 1.0f,
                                                                 0.5f)
                       })
    
                                     
                                     
#endif
{
    gainParameter = parameters.getRawParameterValue("gain");
}

Try2AudioProcessor::~Try2AudioProcessor()
{
}

//==============================================================================
const String Try2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Try2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Try2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Try2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Try2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Try2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Try2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Try2AudioProcessor::setCurrentProgram (int index)
{
}

const String Try2AudioProcessor::getProgramName (int index)
{
    return {};
}

void Try2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Try2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    currentsamplerate = sampleRate;
    updateAngleDelta();
}

void Try2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Try2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif


void Try2AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)

{

    ScopedNoDenormals noDenormals;

    auto totalNumInputChannels  = getTotalNumInputChannels();

    auto totalNumOutputChannels = getTotalNumOutputChannels();
    

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


       


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            auto currentSineValue = (float)std::sin(currentangle);
            currentangle += angledelta;
            channelData[sample] = channelData[sample] * currentSineValue * *gainParameter;
       
        }
        
    }


}

//==============================================================================
bool Try2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Try2AudioProcessor::createEditor()
{
    return new Try2AudioProcessorEditor (*this, parameters);
}


//==============================================================================
void Try2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Try2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}
void Try2AudioProcessor::updateAngleDelta()
{
    auto cyclespersample = 2000.0/currentsamplerate;
    angledelta = cyclespersample * 2.0 * MathConstants<double>::pi;
}
//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Try2AudioProcessor();
}
