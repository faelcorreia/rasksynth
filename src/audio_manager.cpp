// audio_manager.h

#include "audio_manager.h"
#include <cstddef>
#include <iostream>

audio_manager::audio_manager() {
	PaError err;
 	
 	err = Pa_Initialize();
 	if( err != paNoError )
 		return;
 	
 	outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
 	if (outputParameters.device == paNoDevice) {
 		return;
	}
 	
 	outputParameters.channelCount = 2;       /* stereo output */
 	outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
 	outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
 	outputParameters.hostApiSpecificStreamInfo = NULL;
}

int audio_manager::patestCallback(
	const void *inputBuffer,
	void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData) {

//	std::cout<<timeInfo->currentTime<<std::endl;

	wave * w = (wave*)userData;
	float *out = (float*)outputBuffer;
	unsigned long i;
	(void) timeInfo; /* Prevent unused variable warnings. */
	(void) statusFlags;
	(void) inputBuffer;
	for( i=0; i<framesPerBuffer; i++ ) {
		//RELEASE
		//if (data->amp == 0) {
		//	data->oldAmp = data->oldAmp >= 0.00001 ? data->oldAmp - 0.00001 : 0;
		//}
		*out++ = w->get_wave_table()[w->get_left_phase()] * w->get_amp();
		*out++ = w->get_wave_table()[w->get_right_phase()] * w->get_amp();
		
		w->set_left_phase(w->get_left_phase() + 1);
		if(w->get_left_phase() >= w->get_table_size())
			w->set_left_phase(w->get_left_phase() - w->get_table_size());			
		
		w->set_right_phase(w->get_right_phase() + 1);
		if(w->get_right_phase() >= w->get_table_size())
			w->set_right_phase(w->get_right_phase() - w->get_table_size());	


	} 
	return paContinue;
}

void audio_manager::streamFinished(void * userData) {
	//paTestData *data = (paTestData *) userData;
}

void audio_manager::open(wave * w) {
	PaError err;
	this->w = w;
 	
 	err = Pa_OpenStream(
           &stream,
           NULL, /* no input */
           &outputParameters,
           SAMPLE_RATE,
           paFramesPerBufferUnspecified,
           paClipOff,      /* we won't output out of range samples so don't bother clipping them */
           patestCallback,
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
