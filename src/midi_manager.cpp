// midi_manager.cpp

#include "midi_manager.h"
#include "midi_message.h"
#include <iostream>
#include <cmath>
#include <bitset>

midi_manager::midi_manager() {
	int type, i;
	w = new wave(44100);
	wgen = new wave_generator();
	audiom = new audio_manager();
	wgen->generate_wave(w, (wave_generator::wave_type)0, 200);
	audiom->open(w);

	std::cout<<"Which wave?"<<std::endl;
	std::string str = "";
	for (i=0; i<4; i++) {
		switch(i) {
			case 0:
				str = "Sine";
				break;
			case 1:
				str = "Square";
				break;
			case 2:
				str = "Saw";
				break;
			case 3:
				str = "Triangle";
				break;
			default:
				break;		
		}

		std::cout<<"["<<(i+1)<<"] "<<str<<std::endl;
	}
	 
	std::cin>>type;
	wtype = (wave_generator::wave_type)type;


	int count = Pm_CountDevices();
	std::cout<<"Select a midi input:"<<std::endl;
	do {
		for (i=0; i<count; i++) {
			std::cout<<"["<<i<<"] "<<Pm_GetDeviceInfo(i)->name<<std::endl;		
		}
		std::cout<<"> ";
		std::cin>>deviceId;
	} while(deviceId < 0 || deviceId > count);

	Pm_OpenInput(&stream, deviceId, NULL, 128, NULL, NULL);
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