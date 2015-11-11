// audio_manager.h

#include <portaudio.h>

#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#define SAMPLE_RATE   (44100)

typedef struct {
 	float * wave;
 	int table_size;
 	int left_phase;
 	int right_phase;
 	char message[20];
}paTestData;

class audio_manager {
private:
	PaStreamParameters outputParameters;
	paTestData data;
	PaStream *stream;
	
public:
   audio_manager();
   void open(float * wave, int table_size);
   void change_note(float * wave, int table_size);
   void stop();
   void terminate();
   static int patestCallback(
   		const void * inputBuffer,
   		void * outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo * timeInfo,
        PaStreamCallbackFlags statusFlags,
        void * userData);
   static void streamFinished(void * userData);
};

#endif