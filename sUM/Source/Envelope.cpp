/*
  ==============================================================================

    Envelope.cpp
    Created: 11 Apr 2018 11:10:45am
    Author:  tmatoke

  ==============================================================================
*/

#include "../../../../Visual Studio 2017/Projects/ElasticSearch/JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(ElasticSearchAudioProcessor& p)	 :
	processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
	
	// WaveType: Saw, ADSR: 1644.8040771, 157.9631653, 0.3723684, 2039.5328369

	attack.setSliderStyle(Slider::SliderStyle::LinearVertical);
	attack.setRange(0.1f, 5000.0f);
	attack.setValue(500.1f);
	attack.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
	addAndMakeVisible(&attack);

	decay.setSliderStyle(Slider::SliderStyle::LinearVertical);
	decay.setRange(0.1f, 5000.0f);
	decay.setValue(200.01f);
	//decay.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
	addAndMakeVisible(&decay);

	sustain.setSliderStyle(Slider::SliderStyle::LinearVertical);
	sustain.setRange(0.0f, 1.0f);
	sustain.setValue(0.1f);
	//sustain.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
	addAndMakeVisible(&sustain);

	release.setSliderStyle(Slider::SliderStyle::LinearVertical);
	release.setRange(0.1f, 5000.0f);
	release.setValue(300.01f);
	//release.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
	addAndMakeVisible(&release);

	attackAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "attack", attack);
	decayAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", decay);
	sustainAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "sustain", sustain);
	releaseAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "release", release);
}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{
	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);
	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.drawText("Envelope", titleArea, Justification::centredTop);

	g.drawText("A", 53, 150, 20, 20, Justification::centredTop);
	g.drawText("D", 77, 150, 20, 20, Justification::centredTop);
	g.drawText("S", 103, 150, 20, 20, Justification::centredTop);
	g.drawText("R", 128, 150, 20, 20, Justification::centredTop);

	juce::Rectangle<float> area(25, 25, 150, 150);

	//g.setColour(Colours::yellow);
	g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Envelope::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
	juce::Rectangle<int> area = getLocalBounds().reduced(50);

	int width = 25;
	int height = 175;

	attack.setBounds(area.removeFromLeft(width).removeFromTop(height).withTrimmedTop(10));
	decay.setBounds(area.removeFromLeft(width).removeFromTop(height).withTrimmedTop(10));
	sustain.setBounds(area.removeFromLeft(width).removeFromTop(height).withTrimmedTop(10));
	release.setBounds(area.removeFromLeft(width).removeFromTop(height).withTrimmedTop(10));
}

void Envelope::sliderValueChanged(Slider* slider) {
	if (slider == &attack) {
		processor.attackTime = attack.getValue();
	}
	else if (slider == &decay) {
		processor.decayTime = decay.getValue();
	}
	else if (slider == &sustain) {
		processor.sustainTime = sustain.getValue();
	}
	else if (slider == &release) {
		processor.releaseTime = release.getValue();
	}
}
