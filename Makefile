CC=g++
CFLAGS=-c -Wall
BUILD_FOLDER=build

all: rasksynth

rasksynth: main wave_generator port_audio
	$(CC) -o bin/rasksynth -g $(BUILD_FOLDER)/*.o -lportaudio

main: src/main.cpp
	$(CC) $(CFLAGS) -o $(BUILD_FOLDER)/main.o -g src/main.cpp -lportaudio

wave_generator: src/wave_generator.cpp
	$(CC) $(CFLAGS) -o $(BUILD_FOLDER)/wave_generator.o -g src/wave_generator.cpp -lportaudio

port_audio: src/port_audio.cpp
	$(CC) $(CFLAGS) -o $(BUILD_FOLDER)/port_audio.o -g src/port_audio.cpp -lportaudio