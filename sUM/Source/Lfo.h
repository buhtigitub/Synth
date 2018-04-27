/*
  ==============================================================================

    Lfo.h
    Created: 17 Apr 2018 11:09:01am
    Author:  tmatoke

  ==============================================================================
*/

#pragma once

#include "../../../../Visual Studio 2017/Projects/ElasticSearch/JuceLibraryCode/JuceHeader.h"
#include "../Source/PluginProcessor.h"

//==============================================================================
/*
*/
class Lfo : public Component {
public:
    Lfo(ElasticSearchAudioProcessor&);
    ~Lfo();

    void paint (Graphics&) override;
    void resized() override;

private:
	ElasticSearchAudioProcessor & processor;

	ComboBox shape;
	Slider frequency;
	Slider phase;
	Slider level;
	ToggleButton oscShape;
	ToggleButton oscFrequency;
	ToggleButton oscShift;
	ToggleButton oscLevel;
	ToggleButton filterFrequency;
	ToggleButton filterResonance;
	ToggleButton envAttack;
	ToggleButton envDelay;
	ToggleButton envSustain;
	ToggleButton envRelease;

	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> shapeAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> frequencyAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> phaseAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> levelAttachment;

	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> oscShapeAttachment;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> oscFrequencyAttachment;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> oscShiftAttachment;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> oscLevelAttachment;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> filterFrequencyAttachment;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> filterResonanceAttachment;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> envAttackAttachment;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> envDelayAttachment;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> envSustainAttachment;
	ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> envReleaseAttachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Lfo)
};