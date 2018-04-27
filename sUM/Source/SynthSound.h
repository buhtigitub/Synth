/*
  ==============================================================================

    SynthSound.h
    Created: 2 Apr 2018 2:19:49pm
    Author:  tmatoke

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound {
public:
	bool appliesToNote(int /*midiNoteNumber*/) {
		return true;
	}

	bool appliesToChannel(int /*midiChannel*/) {
		return true;
	}
};