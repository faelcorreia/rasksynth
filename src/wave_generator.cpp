// wave_generator.cpp

#include "wave_generator.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

void wave_generator::print_wave(wave * w, int size) {
   int i, j;
   int offset = 30;
   for (i=0; i<size; i++) {
      int max = w->get_wave_table()[i] * offset;
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

void wave_generator::generate_wave(wave * w, wave_type type, int size) {
   switch(type) {
      case BLANK:
         blank(w, size);
         break;
      case SINE:
         sine(w, size);
         break;
      case SQUARE:
         square(w, size);
         break;
      case SAW:
         saw(w, size);
         break;
      case TRIANGLE:
         triangle(w, size);
         break;
      default:
         break;
   }
   w->set_table_size(size);
}

void wave_generator::blank(wave * w, int size) {
   int i;
   for(i=0; i<size; i++) {
      w->get_wave_table()[i] = 0;
   }
}

void wave_generator::sine(wave * w, int size) {
   int i;
   float fsize = (float)size;
   for(i=0; i<size; i++) {
      w->get_wave_table()[i] = (float) sin(2. * M_PI * ((float)i/(fsize+1.)));
   }
}

void wave_generator::square(wave * w, int size) {
   int i;
   w->get_wave_table()[0] = 0;
   w->get_wave_table()[size-1] = 0;
   for(i=1; i<size-1; i++) {
      w->get_wave_table()[i] = i<size/2 ? 1 : -1;      
   }
}

void wave_generator::saw(wave * w, int size) {
   int i;
   float fsize = (float)size;
   for(i=0; i<size-1; i++) {
      w->get_wave_table()[i] = 1 - (1. / (fsize/2.) * i);
   }
}

void wave_generator::triangle(wave * w, int size) {
   int i;
   float fsize = (float)size;
   for(i=0; i<size; i++) { 
      if (i <= size/2)
         w->get_wave_table()[i] = -1 + (2./(fsize/2.)) * i;
      else
         w->get_wave_table()[i] = 3 - (2./(fsize/2.)) * i;
   }
}