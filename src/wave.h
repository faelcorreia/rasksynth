// wave.h

#ifndef WAVE_H
#define WAVE_H

class wave {
	private:
		float * wave_table;
	 	int table_size;
	 	float left_phase;
	 	float right_phase;
	  	float amp;
	  	bool mute;
	  	float freq;
	public:
		wave(int sample_rate);
		float * get_wave_table();
		int get_table_size();
		void set_table_size(int table_size);
		float get_left_phase();
		float get_right_phase();
		void set_left_phase(float left_phase);
		void set_right_phase(float right_phase);
		float get_amp();
		void set_amp(float amp);
		bool get_mute();
		void set_mute(bool mute);
		float get_freq();
		void set_freq(float freq);
};

#endif