/*
  ==============================================================================

    Filter.h
    Created: 11 Apr 2018 12:36:40pm
    Author:  tmatoke

  ==============================================================================
*/

#pragma once

#include "../../../../Visual Studio 2017/Projects/ElasticSearch/JuceLibraryCode/JuceHeader.h"
#include "../Source/PluginProcessor.h"

//==============================================================================
/*
*/
class Filter : public Component
{
public:
    Filter(ElasticSearchAudioProcessor&);
    ~Filter();
    void paint (Graphics&) override;
    void resized() override;

private:
	ElasticSearchAudioProcessor& processor;

	ComboBox filterMenu;
	Slider frequency;
	Slider resonance;

	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> typeAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> frequencyAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resonanceAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
