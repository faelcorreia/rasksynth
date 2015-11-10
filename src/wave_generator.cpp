// wave_generator.cpp

#include "wave_generator.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

void print_wave(float * wave, int size) {
   int i, j;
   int offset = 30;
   for (i=0; i<size; i++) {
      int max = wave[i] * offset;
      for (j=-1 * offset; j<=offset; j++) {
         if (j == 0)
            std::cout<<"|";
         else if (j == max)
            std::cout<<"#";
         else
            std::cout<<" ";
      }
      std::cout<<std::endl;
   }   
}

float * wave_generator::generate_wave(wave_type type, int size) {
   float * wave;
   switch(type) {
      case SINE:
         wave = sine(size);
         break;
      case SQUARE:
         wave = square(size);
         break;
      case SAW:
         wave = saw(size);
         break;
      case TRIANGLE:
         wave = triangle(size);
         break;
      default:
         break;
   }
   return wave;
}

float * wave_generator::sine(int size) {
   int i;
   float * wave = new float[size];
   float fsize = (float)size;
   for(i=0; i<size; i++) {
      wave[i] = (float) sin(2. * M_PI * ((float)i/(fsize+1.)));
   }
   print_wave(wave, size);
   return wave;
}

float * wave_generator::square(int size) {
   int i;
   float * wave = new float[size];
   wave[0] = 0;
   wave[size-1] = 0;
   for(i=1; i<size-1; i++) {
      wave[i] = i<size/2 ? 1 : -1;      
   }
   print_wave(wave, size);
   return wave;
}

float * wave_generator::saw(int size) {
   int i;
   float * wave = new float[size];
   float fsize = (float)size;
   for(i=0; i<size-1; i++) {
      wave[i] = 1 - (1. / (fsize/2.) * i);
   }
   print_wave(wave, size);
   return wave;
}

float * wave_generator::triangle(int size) {
   int i;
   float * wave = new float[size];
   float fsize = (float)size;
   for(i=0; i<size; i++) { 
      if (i <= size/2)
         wave[i] = -1 + (2./(fsize/2.)) * i;
      else
         wave[i] = 3 - (2./(fsize/2.)) * i;
   }
   print_wave(wave, size);
   return wave;
}