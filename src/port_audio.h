// port_audio.h

#include <portaudio.h>

#ifndef PORT_AUDIO_H
#define PORT_AUDIO_H

#define NUM_SECONDS   (5)
#define SAMPLE_RATE   (44100)
#define FRAMES_PER_BUFFER  (64)

#ifndef M_PI
#define M_PI  (3.14159265)
#endif

typedef struct {
 	float * wave;
 	int table_size;
 	int left_phase;
 	int right_phase;
 	char message[20];
}paTestData;

class port_audio {
private:
	PaStreamParameters outputParameters;
	paTestData data;
	PaStream *stream;
	
public:
   port_audio();
   void play(float * wave, int table_size);
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