/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Try2AudioProcessorEditor::Try2AudioProcessorEditor (Try2AudioProcessor& p, AudioProcessorValueTreeState& vts)
: AudioProcessorEditor (&p), processor (p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (100, 300);
    gainSlider.setRange(0.0, 1.0);
    gainSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainSlider.setValue(0.5);
    gainSlider.addListener(this);
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    gainAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "gain", gainSlider));
     
       
    
    
    addAndMakeVisible(gainSlider);
    gainSlider.setTextValueSuffix ("Ring Modulator");
}

Try2AudioProcessorEditor::~Try2AudioProcessorEditor()
{
}

//==============================================================================
void Try2AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
g.fillAll (Colours::floralwhite);
      
    g.setColour (Colours::floralwhite);
    g.setFont (10.0f);
    g.setColour (Colours::teal);
    g.drawFittedText ("Ring Modulator", 0, 0, getWidth(), 30, Justification::centred, 1);
    
   
 
    
    
    
}
void Try2AudioProcessorEditor::resized()
{
    //gainSlider.setBounds(getLocalBounds());
    gainSlider.setBounds (40, 30, 20, getHeight() - 60);
    
}
    
    
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

        void Try2AudioProcessorEditor::sliderValueChanged(Slider *slider)

{
    if(slider ==&gainSlider)
    {
        processor.rawVolume = gainSlider.getValue();
    }
}


