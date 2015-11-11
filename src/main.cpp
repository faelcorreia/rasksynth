#include <iostream>
#include "midi_manager.h"

int arr[] = {440, 293, 329, 349, 392};

int main(void) {
	midi_manager * midim = new midi_manager();
	midim->start_read();
}