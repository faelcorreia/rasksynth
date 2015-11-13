// midi_message.h

#ifndef MIDI_MESSAGE_H
#define MIDI_MESSAGE_H

#include <stdint.h>

class midi_message {
	private:
		uint8_t channel;
		bool note_on;
		uint8_t note;
		uint8_t velocity;
	public:
		midi_message(long message);
		bool get_note_on();
		uint8_t get_note();
		uint8_t get_velocity();
};

#endif