CC=g++
CFLAGS=-c -Wall -Iinclude
LIBS=-lportaudio -lportmidi
BUILD_FOLDER=build

all: rasksynth

rasksynth: main wave_generator audio_manager midi_manager
	$(CC) -o bin/rasksynth -g $(BUILD_FOLDER)/*.o $(LIBS)

main: src/main.cpp
	$(CC) $(CFLAGS) -o $(BUILD_FOLDER)/main.o -g src/main.cpp

wave_generator: src/wave_generator.cpp
	$(CC) $(CFLAGS) -o $(BUILD_FOLDER)/wave_generator.o -g src/wave_generator.cpp 

audio_manager: src/audio_manager.cpp
	$(CC) $(CFLAGS) -o $(BUILD_FOLDER)/audio_manager.o -g src/audio_manager.cpp

midi_manager: src/midi_manager.cpp
	$(CC) $(CFLAGS) -o $(BUILD_FOLDER)/midi_manager.o -g src/midi_manager.cpp