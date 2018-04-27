/*
  ==============================================================================

    SynthVoice.h
    Created: 2 Apr 2018 2:20:05pm
    Author:  tmatoke

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public SynthesiserVoice {
public:
	
	bool canPlaySound(SynthesiserSound* sound) {
		return dynamic_cast<SynthSound*>(sound) != nullptr;
	}

	double getFrequency() {
		return frequency * ((oscFrequency) ? (getLfoShape() + 0.5) : 1);
		//return frequency;
	}

	void setWaveType(float* type) {
		waveShape = *type;
	}
	double getWave() {
		//push shape value up using mod and waveShape
		int shape = (oscShape)? (getLfoShape() * 3.0 + waveShape) : waveShape;
		if (shape > 3) {
			shape -= 3;
		}
		if (shape < 1) {
			//return osc.sinewave(getFrequency());
			return osc.sinewave(getFrequency()) * ((oscShift) ? (getLfoShape() + 0.5) : 1);
		}
		else if (shape < 2) {
			return osc.saw(getFrequency()) * ((oscShift) ? (getLfoShape() + 0.5) : 1);
		}
		else if (shape < 3) {
			return osc.square(getFrequency()) * ((oscShift) ? (getLfoShape() + 0.5) : 1);
		}
		else {
			return osc.sinewave(getFrequency()) * ((oscShift) ? (getLfoShape() + 0.5) : 1);
		}
	}

	double getEnvelope() {
		return env.adsr(getWave(), env.trigger) * ((oscLevel) ? (getLfoShape() + 0.5) : 1);
	}

	// are these called constantly?
	void setAttack(float* attack) {
		env.setAttack(double(*attack));
	}
	void setDecay(float* decay) {
		env.setDecay(double(*decay));
	}
	void setSustain(float* sustain) {
		env.setSustain(double(*sustain));
	}
	void setRelease(float* release) {
		env.setRelease(double(*release));
	}

	void setFilterType(float* type) {
		filterType = *type;
	}
	void setFilterFrequency(float* selection) {
		filter.cutoff = (*selection);
	}
	double getFilterFrequency() {
		return filter.cutoff * ((filterFrequency) ? (getLfoShape() + 0.5) : 1);
	}
	void setFilterResonance(float* selection) {
		filter.resonance = *selection;
	}
	double getFilterResonance() {
		return filter.resonance * ((filterResonance) ? (getLfoShape() + 0.5) : 1);
	}
	double getFilter() {
		if (filterType == 0) {
			return filter.lores(getEnvelope(), getFilterFrequency(), getFilterResonance());
		}
		else if (filterType == 1) {
			return filter.hires(getEnvelope(), filter.cutoff, filter.resonance);
		}
		else if (filterType == 2) {
			return filter.bandpass(getEnvelope(), filter.cutoff, filter.resonance);
		}
		else {
			return filter.lores(getEnvelope(), filter.cutoff, filter.resonance);
		}
	}

	void setLfoShape(float* shape) {
		lfoShape = *shape;
	}
	double getLfoShape() {
		if (lfoShape == 0) {
			return lfo.sinewave(lowFrequency)*lfoLevel;
		}
		else if (lfoShape == 1) {
			return lfo.triangle(lowFrequency)*lfoLevel;
		}
		else if (lfoShape == 2) {
			return lfo.saw(lowFrequency)*lfoLevel;
		}
		else {
			return lfo.sinewave(lowFrequency)*lfoLevel;
		}
	}
	void setLowFrequency(float* selection) {
		lowFrequency = *selection;
	}
	void setLfoPhase(float* selection) {
		lfoPhase = *selection;
	}
	void setLfoLevel(float* selection) {
		lfoLevel = *selection;
	}

	void setLfoOscShape(float* selection) {
		oscShape = *selection;
	}
	void setLfoOscFrequency(float* selection) {
		oscFrequency = *selection;
	}
	void setLfoOscShift(float* selection) {
		oscShift = *selection;
	}
	void setLfoOscLevel(float* selection) {
		oscLevel = *selection;
	}

	void setLfoFilterFrequency(float* selection) {
		filterFrequency = *selection;
	}
	void setLfoFilterResonance(float* selection) {
		filterResonance = *selection;
	}

	void setLfoEnvAttack(float* selection) {
		envAttack = *selection;
	}
	void setLfoEnvDelay(float* selection) {
		envDelay = *selection;
	}
	void setLfoEnvSustain(float* selection) {
		envSustain = *selection;
	}
	void setLfoEnvRelease(float* selection) {
		envRelease = *selection;
	}

	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) {
		env.trigger = 1;
		level = velocity;
		frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	}

	void stopNote(float velocity, bool allowTailOff) {
		env.trigger = 0;
		allowTailOff = true;

		if (velocity == 0) {
			clearCurrentNote();
		}
	}

	void pitchWheelMoved(int newPitchWheelValue) {
		
	}

	void controllerMoved(int controllerNumber, int newControllerValue) {
		
	}

	void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
		for (int sample = 0; sample < numSamples; ++sample) {
			for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
				outputBuffer.addSample(channel, startSample, getFilter());
			}
			++startSample;
		}
	}

private:
	double level = 1.0, frequency, lowFrequency, lfoPhase, lfoLevel;
	int waveShape, filterType, lfoShape;
	// Move all into an array or structure that can be accessed by name
	boolean oscShape, oscFrequency, oscShift, oscLevel, filterFrequency, filterResonance, envAttack, envDelay, envSustain, envRelease;
	maxiOsc osc;
	maxiEnv env;
	maxiFilter filter;
	maxiOsc lfo;
};
