/*
  ==============================================================================

    Oscillator.h
    Created: 10 Apr 2018 2:07:15pm
    Author:  tmatoke

  ==============================================================================
*/

#pragma once

#include "../../../../Visual Studio 2017/Projects/ElasticSearch/JuceLibraryCode/JuceHeader.h"
#include "../Source/PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator    : public Component,
	private ComboBox::Listener
{
public:
    Oscillator(ElasticSearchAudioProcessor&);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;

	void comboBoxChanged(ComboBox*) override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	ElasticSearchAudioProcessor & processor;

	ComboBox oscMenu;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
