// midi_manager.h

#ifndef MIDI_MANAGER_H
#define MIDI_MANAGER_H

#include <portmidi.h>
#include "audio_manager.h"
#include "wave_generator.h"

class midi_manager {
	private:
		PortMidiStream *stream;
		int deviceId;
		audio_manager * audiom;
		float * wave;
		wave_generator * wgen;
		wave_generator::wave_type wtype;	
	public:
		midi_manager();
		void start_read();
		float note_to_hertz(int note);
};

#endif