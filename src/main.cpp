#include <iostream>
#include "midi_manager.h"
#include "wave_generator.h"
#include "audio_manager.h"

int arr[] = {440, 293, 329, 349, 392};

int main(void) {
	int i, type;
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
	std::cout<<"> ";
	std::cin>>type;

	wave_generator::wave_type wtype = (wave_generator::wave_type)type;

	audio_manager * audiom = new audio_manager();
	wave_generator * wgen = new wave_generator();

	midi_manager * midim = new midi_manager(wgen, wtype, audiom);

	int count = midim->get_count(), deviceId;
	std::cout<<"Select a midi input:"<<std::endl;
	do {
		for (i=0; i<count; i++) {
			std::cout<<"["<<i<<"] "<<midim->get_device_name(i)<<std::endl;		
		}
		std::cout<<"> ";
		std::cin>>deviceId;
	} while(deviceId < 0 || deviceId > count);

	midim->set_device(deviceId);
	midim->start_read();
}