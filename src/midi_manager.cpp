// midi_manager.cpp

#include "midi_manager.h"
#include <iostream>
#include <cmath>
#include <bitset>

midi_manager::midi_manager() {
	int type;
	wgen = new wave_generator();
	audiom = new audio_manager();
	wave = new float[12544];
	wgen->generate_wave(wave, (wave_generator::wave_type)0, 200);
	audiom->open(wave, 200);

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
	int note, noteOn, size;
	while (true) {
		Pm_Read(stream, &data, 1);
		
		std::bitset<8> note_message = std::bitset<8>((data.message >> 8));
		note = note_message.to_ulong();

		std::bitset<1> noteOn_message = std::bitset<1>((data.message >> 22));
		noteOn = noteOn_message.to_ulong();

		if (noteOn == 1) {
			size = (int)(44100. / note_to_hertz(note));
			wgen->generate_wave(wave, wtype, size);
		}
		else {
			wgen->generate_wave(wave, (wave_generator::wave_type)0, 200);	
		}
		
		audiom->change_note(wave, size);
	}
}