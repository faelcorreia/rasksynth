// wave.cpp

#include "wave.h"

wave::wave(int sample_rate) {
	int i;
	table_size = sample_rate;
	wave_table = new float[table_size];
	for (i=0; i<table_size; i++)
		wave_table[i] = 0;
	left_phase = right_phase = 0;
	amp = 0.;
	mute = 0;
	freq = 1;
}

float * wave::get_wave_table() {
	return wave_table;
}

int wave::get_table_size() {
	return table_size;
}

void wave::set_table_size(int table_size) {
	this->table_size = table_size;
}

float wave::get_left_phase() {
	return left_phase;
}

float wave::get_right_phase() {
	return right_phase;
}

void wave::set_left_phase(float left_phase) {
	this->left_phase = left_phase;
}

void wave::set_right_phase(float right_phase) {
	this->right_phase = right_phase;
}

float wave::get_amp() {
	return amp;
}

void wave::set_amp(float amp) {
	this->amp = amp;
}

bool wave::get_mute() {
	return mute;
}

void wave::set_mute(bool mute) {
	this->mute = mute;
}

float wave::get_freq() {
	return freq;
}

void wave::set_freq(float freq) {
	this->freq = freq;
}