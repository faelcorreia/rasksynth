// wave.h

#ifndef WAVE_H
#define WAVE_H

#define MAX_TABLE_SIZE 12545

class wave {
private:
	float * wave_table;
 	int table_size;
 	int left_phase;
 	int right_phase;
  	float amp;
public:
	wave(int sample_rate);
	float * get_wave_table();
	int get_table_size();
	void set_table_size(int table_size);
	int get_left_phase();
	int get_right_phase();
	void set_left_phase(int left_phase);
	void set_right_phase(int right_phase);
	float get_amp();
	void set_amp(float amp);
};

#endif