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

void wave_generator::generate_wave(float * wave, wave_type type, int size) {
   switch(type) {
      case BLANK:
         blank(wave, size);
         break;
      case SINE:
         sine(wave, size);
         break;
      case SQUARE:
         square(wave, size);
         break;
      case SAW:
         saw(wave, size);
         break;
      case TRIANGLE:
         triangle(wave, size);
         break;
      default:
         break;
   }   
}

void wave_generator::blank(float * wave, int size) {
   int i;
   for(i=0; i<size; i++) {
      wave[i] = 0;
   }
}

void wave_generator::sine(float * wave, int size) {
   int i;
   float fsize = (float)size;
   for(i=0; i<size; i++) {
      wave[i] = (float) sin(2. * M_PI * ((float)i/(fsize+1.)));
   }
}

void wave_generator::square(float * wave, int size) {
   int i;
   wave[0] = 0;
   wave[size-1] = 0;
   for(i=1; i<size-1; i++) {
      wave[i] = i<size/2 ? 1 : -1;      
   }
}

void wave_generator::saw(float * wave, int size) {
   int i;
   float fsize = (float)size;
   for(i=0; i<size-1; i++) {
      wave[i] = 1 - (1. / (fsize/2.) * i);
   }
}

void wave_generator::triangle(float * wave, int size) {
   int i;
   float fsize = (float)size;
   for(i=0; i<size; i++) { 
      if (i <= size/2)
         wave[i] = -1 + (2./(fsize/2.)) * i;
      else
         wave[i] = 3 - (2./(fsize/2.)) * i;
   }
}