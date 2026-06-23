#ifndef SOUNDFONT_H
#include <map>
#include "fluidsynth.h"
#include <string>
#include <iostream>
#include <MidiFile.h>
#define SOUNDFONT_H

class SoundFont{
    private: 
        // file location of the sound font
        std::string file;
        // map where it stores the instrument number and a bool that
        // indicates if the instrument is supported
        std::map<int,bool> instruments;
    public:
        // constructor
        SoundFont(char* file);
        std::string get_file()const;
        bool verify_instrument(int instrument_num)const;
        void display_instruments();
        void clean_up(fluid_settings_t* settings,fluid_synth_t* synth);
};

#endif