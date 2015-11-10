// wave_generator.h

#ifndef WAVE_GENERATOR_H
#define WAVE_GENERATOR_H

class wave_generator {
private:
	float * sine(int size);
	float * square(int size);
	float * saw(int size);
	float * triangle(int size);

public:
	enum wave_type { SINE = 0, SQUARE = 1, SAW = 2, TRIANGLE = 3};
	float * generate_wave(wave_type type, int size);
};

#endif