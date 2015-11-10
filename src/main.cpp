#include <iostream>
#include "wave_generator.h"
#include "port_audio.h"

int arr[] = {440, 293, 329, 349, 392};

int main(void) {
	int size, type;
	wave_generator::wave_type wtype;
	char note;
	bool playing = 0;
	wave_generator * wgen = new wave_generator();
	port_audio * paudio = new port_audio();
	std::cout<<"Which wave [0 for sine, 1 for square, 2 for saw, 3 for triangle]? ";
	std::cin>>type;
	wtype = (wave_generator::wave_type)type;
	while(true) {
		std::cin>>note;
		size = 44100 / arr[(note - '0')-1];
		if (!playing) {
			paudio->play(wgen->generate_wave(wtype, size), size);
			playing = 1;
		}
		else {
			paudio->change_note(wgen->generate_wave(wtype, size), size);
		}
	}
}