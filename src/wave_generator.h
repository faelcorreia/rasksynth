// wave_generator.h

#ifndef WAVE_GENERATOR_H
#define WAVE_GENERATOR_H

class wave_generator {
private:
	void blank(float * wave, int size);
	void sine(float * wave, int size);
	void square(float * wave, int size);
	void saw(float * wave, int size);
	void triangle(float * wave, int size);

public:
	enum wave_type { BLANK = 0, SINE = 1, SQUARE = 2, SAW = 3, TRIANGLE = 4};
	void generate_wave(float * wave, wave_type type, int size);
};

#endif