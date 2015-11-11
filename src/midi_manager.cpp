// midi_manager.cpp

#include "midi_manager.h"
#include "midi_message.h"
#include <cmath>

midi_manager::midi_manager(wave_generator * wgen, wave_generator::wave_type wtype, audio_manager * audiom) {
	w = new wave(44100);
	this->wgen = wgen;
	this->audiom = new audio_manager();
	this->wtype = wtype;	
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
	int note, noteOn, velocity, size, sum = 0;
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
			
			if (sum == 0) {
				amp = 0;
			}
			else {
				size = (int)(44100. / note_to_hertz(note));
				amp = ((float)velocity/127.) * 0.3;				
			}
			wgen->generate_wave(w, wtype, size+1);
			w->set_amp(amp);			
		}
		Pa_Sleep(10);
	}
}