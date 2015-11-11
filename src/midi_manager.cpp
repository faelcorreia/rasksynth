// midi_manager.cpp

#include "midi_manager.h"
#include <iostream>
#include <cmath>
#include <bitset>

midi_manager::midi_manager() {
	int type;
	w = new wave(44100);
	wgen = new wave_generator();
	audiom = new audio_manager();
	wgen->generate_wave(w, (wave_generator::wave_type)0, 200);
	audiom->open(w);

	std::cout<<"Which wave [1 for sine, 2 for square, 3 for saw, 4 for triangle]? "<<std::endl<<"> ";
	std::cin>>type;
	wtype = (wave_generator::wave_type)type;


	int count = Pm_CountDevices(), i;
	std::cout<<"Select a midi input: "<<std::endl;
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
	int note, noteOn, sum = 0, velocity, size;
	float amp;
	while (true) {
		if (Pm_Poll(stream)) {
			Pm_Read(stream, &data, 1);
			std::bitset<8> noteOn_message = std::bitset<8>(data.message);
			noteOn = noteOn_message.to_ulong();
			sum += noteOn > 128 ? 1 : -1;

			if (noteOn > 128) {
				std::bitset<8> note_message = std::bitset<8>((data.message >> 8));
				note = note_message.to_ulong();	

				std::bitset<8> velocity_message = std::bitset<8>((data.message >> 16));
				velocity = velocity_message.to_ulong();
			}

			std::cout<<"Notes on: "<<sum<<" | Note: "<<note<<" | Velocity: "<<velocity<<std::endl;
			
			
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