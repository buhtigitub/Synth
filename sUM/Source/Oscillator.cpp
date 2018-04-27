/*
  ==============================================================================

    Oscillator.cpp
    Created: 10 Apr 2018 2:07:15pm
    Author:  tmatoke

  ==============================================================================
*/

#include "../../../../Visual Studio 2017/Projects/ElasticSearch/JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(ElasticSearchAudioProcessor& p) : processor(p) {
	setSize(200, 200);

	oscMenu.addItem("Sine", 1);
	oscMenu.addItem("Saw", 2);
	oscMenu.addItem("Square", 3);
	oscMenu.setJustificationType(Justification::centred);
	addAndMakeVisible(&oscMenu);
	oscMenu.addListener(this);

	// Add level and master fine control
	// Add frequency meter than also tracks the lfo's effect

	waveAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "waveType", oscMenu);
}

Oscillator::~Oscillator() {
}

void Oscillator::paint (Graphics& g) {
	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);
	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.drawText("Osc 1", titleArea, Justification::centredTop);

	juce::Rectangle<float> area(25, 25, 150, 150);
	//g.setColour(Colours::yellow);
	g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Oscillator::resized() {
    // This method is where you should set the bounds of any child
    // components that your component contains..

	juce::Rectangle<int> area = getLocalBounds().reduced(40);
	oscMenu.setBounds(area.removeFromTop(20));
}

void Oscillator::comboBoxChanged(ComboBox* comboBox) {
	
}