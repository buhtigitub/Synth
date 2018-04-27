/*
  ==============================================================================

    Lfo.cpp
    Created: 17 Apr 2018 11:09:01am
    Author:  tmatoke

  ==============================================================================
*/

#include "../../../../Visual Studio 2017/Projects/ElasticSearch/JuceLibraryCode/JuceHeader.h"
#include "Lfo.h"

//==============================================================================
Lfo::Lfo(ElasticSearchAudioProcessor& p) : processor(p) {
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.
	setSize(200, 400);

	shape.addItem("Sine", 1);
	shape.addItem("Tri", 2);
	shape.addItem("Saw", 3);
	shape.addItem("iSaw", 4);
	shape.setJustificationType(Justification::centred);
	addAndMakeVisible(&shape);
	shapeAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "lfoShape", shape);

	frequency.setSliderStyle(Slider::SliderStyle::LinearVertical);
	frequency.setRange(0.05, 72.0);	// (0.05, 72.0) https://tomhess.net/Tools/DelayCalculator.aspx .25 hertz is 1 beat per second. At a bpm of 60, .06125 hertz is every 8 beats. At a bpm of 180, 72 hertz is every 1/64T beats, 48 hertz is every 1/64 beats.
	frequency.setValue(0.5);
	//frequency.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	frequency.setSkewFactorFromMidPoint(1000.0);
	//frequency.setTextBoxIsEditable(true);
	frequencyAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "lowFrequency", frequency);
	addAndMakeVisible(&frequency);

	phase.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	phase.setRange(0, 180);
	phase.setValue(0);
	phase.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	phaseAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "lfoPhase", phase);
	addAndMakeVisible(&phase);

	level.setSliderStyle(Slider::SliderStyle::LinearVertical);
	level.setRange(0.0f, 1.0f);
	level.setValue(0.5f);
	//level.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	levelAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "lfoLevel", level);
	addAndMakeVisible(&level);

	oscShape.setButtonText("Osc Shape");
	oscShape.changeWidthToFitText();
	oscShapeAttachment = new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "lfoOscShape", oscShape);
	addAndMakeVisible(&oscShape);
	oscFrequency.setButtonText("OSC Frequency");
	oscFrequency.changeWidthToFitText();
	oscFrequencyAttachment = new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "lfoOscFrequency", oscFrequency);
	addAndMakeVisible(&oscFrequency);
	oscShift.setButtonText("OSC Shift");
	oscShift.changeWidthToFitText();
	oscShiftAttachment = new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "lfoOscShift", oscShift);
	addAndMakeVisible(&oscShift);
	oscLevel.setButtonText("OSC Level");
	oscLevel.changeWidthToFitText();
	oscLevelAttachment = new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "lfoOscLevel", oscLevel);
	addAndMakeVisible(&oscLevel);


	filterFrequency.setButtonText("Filter Frequency");
	filterFrequencyAttachment = new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "lfoFilterFrequency", filterFrequency);
	addAndMakeVisible(&filterFrequency);
	filterResonance.setButtonText("Filter Resonance");
	filterResonanceAttachment = new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "lfoFilterResonance", filterResonance);
	addAndMakeVisible(&filterResonance);

	envAttack.setButtonText("Env Attack");
	envAttackAttachment = new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "lfoEnvAttack", envAttack);
	addAndMakeVisible(&envAttack);
	envDelay.setButtonText("Env Delay");
	envDelayAttachment = new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "lfoEnvDelay", envDelay);
	addAndMakeVisible(&envDelay);
	envSustain.setButtonText("Env Sustain");
	envSustainAttachment = new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "lfoEnvSustain", envSustain);
	addAndMakeVisible(&envSustain);
	envRelease.setButtonText("Env Release");
	envReleaseAttachment = new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "lfoEnvRelease", envRelease);
	addAndMakeVisible(&envRelease);
}

Lfo::~Lfo() {

}

void Lfo::paint (Graphics& g) {
	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);
	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.drawText("Lfo", titleArea, Justification::centredTop);

	juce::Rectangle<float> area(25, 25, getWidth()-50, 150);
	g.setColour(Colours::grey);
	g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Lfo::resized() {
    // This method is where you should set the bounds of any child
    // components that your component contains..
	juce::Rectangle<int> area = getLocalBounds().reduced(40);

	int width = 25;
	int height = 175;

	shape.setBounds(area.removeFromTop(20));
	frequency.setBounds(area.removeFromLeft(width + 20).removeFromTop(height).withTrimmedTop(10));
	level.setBounds(area.removeFromLeft(width + 20).removeFromTop(height).withTrimmedTop(10));

	oscShape.setBounds(230, 60, 160, 20);
	oscFrequency.setBounds(230, 80, 160, 20);
	oscLevel.setBounds(230, 100, 160, 20);
	oscShift.setBounds(230, 120, 160, 20);
	filterFrequency.setBounds(230, 140, 160, 20);
	filterResonance.setBounds(370, 140, 160, 20);
	envAttack.setBounds(370, 60, 160, 20);
	envDelay.setBounds(370, 80, 160, 20);
	envSustain.setBounds(370, 100, 160, 20);
	envRelease.setBounds(370, 120, 160, 20);
}