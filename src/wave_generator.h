// wave_generator.h

#ifndef WAVE_GENERATOR_H
#define WAVE_GENERATOR_H

#include "wave.h"

class wave_generator {
	private:
		void blank(wave * w, int size);
		void sine(wave * w, int size);
		void square(wave * w, int size);
		void saw(wave * w, int size);
		void triangle(wave * w, int size);
		void white_noise(wave * w, int size);
	public:
		enum wave_type { BLANK = 0, SINE = 1, SQUARE = 2, SAW = 3, TRIANGLE = 4, WHITE_NOISE = 5};
		void generate_wave(wave * w, wave_type type, int size);
		void print_wave(wave * w, int size, int freq);
};

#endif