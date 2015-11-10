// port_audio.h

#include "port_audio.h"
#include <cstddef>

port_audio::port_audio() {
	PaError err;
 	
 	data.left_phase = data.right_phase = 0;

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

int port_audio::patestCallback(
	const void *inputBuffer,
	void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData) {

	paTestData *data = (paTestData*)userData;
	float *out = (float*)outputBuffer;
	unsigned long i;
	(void) timeInfo; /* Prevent unused variable warnings. */
	(void) statusFlags;
	(void) inputBuffer;
	for( i=0; i<framesPerBuffer; i++ ) {
		*out++ = data->wave[data->left_phase];  
		*out++ = data->wave[data->right_phase]; 
		data->left_phase += 1;
		if(data->left_phase >= data->table_size)
			data->left_phase -= data->table_size;
		
		data->right_phase += 1;
		if( data->right_phase >= data->table_size )
			data->right_phase -= data->table_size;


	} 
	return paContinue;
}

void port_audio::streamFinished(void * userData) {
	//paTestData *data = (paTestData *) userData;
}

void port_audio::play(float * wave, int table_size) {
	PaError err;
	data.table_size = table_size;
	data.wave = wave;
 	
 	err = Pa_OpenStream(
           &stream,
           NULL, /* no input */
           &outputParameters,
           SAMPLE_RATE,
           paFramesPerBufferUnspecified,
           paClipOff,      /* we won't output out of range samples so don't bother clipping them */
           patestCallback,
           &data );
	if(err != paNoError)
		return;

	err = Pa_SetStreamFinishedCallback( stream, &streamFinished );
 	if(err != paNoError)
 		return;

 	err = Pa_StartStream(stream);
 	if(err != paNoError)
 		return;
}

void port_audio::change_note(float * wave, int table_size) {
	data.table_size = table_size;
	data.wave = wave;
}

void port_audio::stop() {
	PaError err;

	err = Pa_StopStream( stream );
 	if( err != paNoError ) 	
 		return;
}

void port_audio::terminate() {
	PaError err;

 	err = Pa_CloseStream( stream );
 	if( err != paNoError )
 		return;

	Pa_Terminate();
}
