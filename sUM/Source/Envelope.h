/*
  ==============================================================================

    Envelope.h
    Created: 11 Apr 2018 11:10:45am
    Author:  tmatoke

  ==============================================================================
*/

#pragma once

#include "../../../../Visual Studio 2017/Projects/ElasticSearch/JuceLibraryCode/JuceHeader.h"
#include "../Source/PluginProcessor.h"

//==============================================================================
/*
*/
class Envelope    : public Component, 
					public Slider::Listener
{
public:
    Envelope(ElasticSearchAudioProcessor&);
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;

	void sliderValueChanged(Slider* slider) override;

private:
	ElasticSearchAudioProcessor& processor;
	
	Slider attack;
	Slider decay; 
	Slider sustain;
	Slider release;
	
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
