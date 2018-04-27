/*
  ==============================================================================

    Filter.cpp
    Created: 11 Apr 2018 12:36:40pm
    Author:  tmatoke

  ==============================================================================
*/

#include "../../../../Visual Studio 2017/Projects/ElasticSearch/JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

//==============================================================================
Filter::Filter(ElasticSearchAudioProcessor& p) :
	processor(p) {
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
	setSize(200, 200);

	filterMenu.addItem("Low Pass", 1);
	filterMenu.addItem("High Pass", 2);
	filterMenu.addItem("Band Pass", 3);
	filterMenu.setJustificationType(Justification::centred);
	addAndMakeVisible(&filterMenu);
	typeAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "type", filterMenu);

	frequency.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	frequency.setRange(20.0, 1000.0);
	frequency.setValue(400.0);
	frequency.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	frequency.setSkewFactorFromMidPoint(1000.0);
	frequencyAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "frequency", frequency);
	addAndMakeVisible(&frequency);

	resonance.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	resonance.setRange(0.0f, 1.0f);
	resonance.setValue(0.0f);
	resonance.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	resonanceAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "resonance", resonance);
	addAndMakeVisible(&resonance);
}

Filter::~Filter() {
}

void Filter::paint (Graphics& g) {
	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);
	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.drawText("Filter", titleArea, Justification::centredTop);

	juce::Rectangle<float>area(25, 25, 150, 150);

	//g.setColour(Colours::yellow);
	g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Filter::resized() {
    // This method is where you should set the bounds of any child
    // components that your component contains..

	juce::Rectangle<int> area = getLocalBounds().reduced(40);

	filterMenu.setBounds(area.removeFromTop(20));
	frequency.setBounds(30, 100, 70, 70);
	resonance.setBounds(100, 100, 70, 70);
}
