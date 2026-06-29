#ifndef ENCODER_H

#include <fluidsynth.h>
#include <MidiFile.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <list>
#include <map>
#include <algorithm>
#include <sndfile.h>
#include <lame/lame.h>
#include <fstream>
#include "SoundFont.h"

#if defined(_WIN32)
#define NOMINMAX 
#include <windows.h>
#define sleep(_t) Sleep(_t * 1000)
#include <cstdint> 
#include <sstream>
#include <process.h>
#define getpid _getpid

#define MEGA_DRIVE "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/sound_fonts/Mega-Drive/The_Ultimate Megadrive_Soundfont.sf2"
#define NES "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/sound_fonts/NES/8bitsf.SF2"
#define SNES "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/sound_fonts/SNES/SuperNintendoEntertainmentSystemV1.2.sf2"
#define EXAMPLE_MIDI "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/Demo Midis/Video Game/bubble-crab-s-stage.mid"
#define TEMP "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/temp songs/temp.midi"
#define WAV "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/WAV songs/TEMP.wav"
#else
#include <stdlib.h>
#include <unistd.h>
#endif
#include <vector>

#define ENCODER_H
class Encoder{
    private:
        std::string file_location;
        const std::string MP3_LOC = "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/MP3/example.mp3";
    public:
        Encoder(std::string file_location);
        void clean_up(SNDFILE *file, FILE *output, lame_t encoder);
        void wav2mp3();
};
#endif