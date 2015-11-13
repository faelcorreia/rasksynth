// audio_manager.h

#include <portaudio.h>
#include "wave.h"

#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#define SAMPLE_RATE   (44100)

class audio_manager {
  private:
  	PaStreamParameters outputParameters;
  	wave * w;
  	PaStream *stream;
    static float transition_amp;   
    
  public:
      audio_manager();
      void open(wave * w);
      void stop();
      void terminate();
      static float get_transition_amp();
      static void set_transition_amp(float amp);
      static int callback(
      		const void * inputBuffer,
      		void * outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo * timeInfo,
        PaStreamCallbackFlags statusFlags,
        void * userData);
      static void streamFinished(void * userData);

};

#endif