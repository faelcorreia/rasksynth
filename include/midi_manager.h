// midi_manager.h

#ifndef MIDI_MANAGER_H
#define MIDI_MANAGER_H

#include <portmidi.h>
#include "audio_manager.h"
#include "wave_generator.h"
#include "wave.h"

class midi_manager {
	private:
		PortMidiStream *stream;
		int deviceId;
		audio_manager * audiom;
		wave * w;	
	public:
		midi_manager(wave * w, audio_manager * audiom);
		void start_read();
		int get_count();
		const char * get_device_name(int id);
		void set_device(int id);
		float note_to_hertz(int note);
};

#endif