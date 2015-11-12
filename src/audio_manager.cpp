// audio_manager.h

#include "audio_manager.h"
#include <cstddef>
#include <iostream>

float audio_manager::transition_amp = 0;

audio_manager::audio_manager() {
	PaError err;

	err = Pa_Initialize();
 	if( err != paNoError )
 		return;
 	
 	outputParameters.device = Pa_GetDefaultOutputDevice();
 	if (outputParameters.device == paNoDevice) {
 		return;
	}
 	
 	outputParameters.channelCount = 2;
 	outputParameters.sampleFormat = paFloat32;
 	outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
 	outputParameters.hostApiSpecificStreamInfo = NULL;
}

int audio_manager::callback(
	const void *inputBuffer,
	void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData) {

	wave * w = (wave*)userData;
	float *out = (float*)outputBuffer;
	float amp = audio_manager::get_transition_amp();
	float step = 0.001;
	unsigned long i;
	(void) timeInfo;
	(void) statusFlags;
	(void) inputBuffer;
	for( i=0; i<framesPerBuffer; i++ ) {
		if (!w->get_mute())
			amp = amp <= w->get_amp() - step ? amp + step : w->get_amp();			
		else
			amp = amp >= step ? amp - step : 0;			

		// @todo CHANGE PHASE TO FLOAT TO BEST INCREMENT

		*out++ = w->get_wave_table()[(int)w->get_left_phase()] * amp;
		*out++ = w->get_wave_table()[(int)w->get_right_phase()] * amp;
		
		w->set_left_phase(w->get_left_phase() + w->get_freq());
		if(w->get_left_phase() >= w->get_table_size())
			w->set_left_phase(w->get_left_phase() - w->get_table_size());			
		
		w->set_right_phase(w->get_right_phase() + w->get_freq());
		if(w->get_right_phase() >= w->get_table_size())
			w->set_right_phase(w->get_right_phase() - w->get_table_size());
	}
	audio_manager::set_transition_amp(amp);
	return paContinue;
}

float audio_manager::get_transition_amp() {
	return transition_amp;
}

void audio_manager::set_transition_amp(float amp) {
	transition_amp = amp;
}

void audio_manager::streamFinished(void * userData) {
	//paTestData *data = (paTestData *) userData;
}

void audio_manager::open(wave * w) {
	PaError err;
	this->w = w;
 	
 	err = Pa_OpenStream(
           &stream,
           NULL,
           &outputParameters,
           SAMPLE_RATE,
           paFramesPerBufferUnspecified,
           paClipOff,
           callback,
           w);
	if(err != paNoError)
		return;

	err = Pa_SetStreamFinishedCallback( stream, &streamFinished );
 	if(err != paNoError)
 		return;

 	err = Pa_StartStream(stream);
 	if(err != paNoError)
 		return;
}

void audio_manager::stop() {
	PaError err;

	err = Pa_StopStream( stream );
 	if( err != paNoError ) 	
 		return;
}

void audio_manager::terminate() {
	PaError err;

 	err = Pa_CloseStream( stream );
 	if( err != paNoError )
 		return;

	Pa_Terminate();
}
