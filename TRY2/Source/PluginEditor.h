/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Try2AudioProcessorEditor  : public AudioProcessorEditor,
                                  public Slider::Listener

{
public:
    Try2AudioProcessorEditor (Try2AudioProcessor&, AudioProcessorValueTreeState& vts);
    ~Try2AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider *slider) override;
    
    

private:
    AudioProcessorValueTreeState& valueTreeState;
    Slider gainSlider;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Try2AudioProcessor& processor;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Try2AudioProcessorEditor)
};
