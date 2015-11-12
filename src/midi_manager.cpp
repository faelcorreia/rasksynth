// midi_manager.cpp

#include "midi_manager.h"
#include "midi_message.h"
#include <cmath>

midi_manager::midi_manager(wave * w, audio_manager * audiom) {
	this->w = w;
	this->audiom = new audio_manager();
	audiom->open(w);	
}

int midi_manager::get_count() {
	return Pm_CountDevices();
}

const char * midi_manager::get_device_name(int id) {
	return Pm_GetDeviceInfo(id)->name;
}

void midi_manager::set_device(int id) {
	Pm_OpenInput(&stream, id, NULL, 128, NULL, NULL);	
}

float midi_manager::note_to_hertz(int note) {
	return (440. * pow(2., ((float)note - 69.)/12.));
}

void midi_manager::start_read() {
	PmEvent data;
	int note, noteOn, velocity, sum = 0;
	float amp;
	while (true) {
		if (Pm_Poll(stream)) {
			Pm_Read(stream, &data, 1);
			
			midi_message ms = midi_message(data.message);

			noteOn = ms.get_note_on();
			
			if (noteOn == 1) {
				sum += 1;
				note = ms.get_note();
				velocity = ms.get_velocity();
			}
			else {
				sum -= 1;
			}

			w->set_mute(sum == 0);
			
			amp = ((float)velocity/127.) * 0.3;
			
			w->set_step((int)note_to_hertz(note));
			w->set_amp(amp);		
		}
		Pa_Sleep(10);
	}
}