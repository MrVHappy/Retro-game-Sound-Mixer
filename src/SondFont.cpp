#include <map>
#include "fluidsynth.h"
#include <string>
#include <iostream>
#include <MidiFile.h>

class SoundFont{
    // private attributes
    private: 
        // file location of the sound font
        char* file;
        // map where it stores the instrument number and a bool that
        // indicates if the instrument is supported
        std::map<int,bool> instruments;

        // attributes used for sound font analysis 
        fluid_synth_t* synth = NULL;
        fluid_settings_t* settings = NULL;
        int sfont_ID;
        fluid_sfont_t* sfont = NULL;

    // constructor
    SoundFont(char* file){
        this->file = file;
        // Create settings
        settings = new_fluid_settings();
        synth = new_fluid_synth(settings);
        sfont_ID = fluid_synth_sfload(synth,this->file, 1);
        sfont = fluid_synth_get_sfont_by_id(synth,sfont_ID);
        // setup for instruments
        // loops through all the instruments
        for (int i = 0; i < 127; i++){
            bool isSupported;
            // if fluid_sfont_get_preset returns NULL then instrument is not supported
            if (fluid_sfont_get_preset(sfont,0,i) == NULL){
                isSupported = false;
            }
            else{
                // else is supported
                isSupported = true;
            }
            // add instrument data to map
            instruments[i] = isSupported;
            
        }
    }

    
    public:
        // return the file location of the soundfont
        char* get_file(){
            return this->file;
        }
        // checks if the sound font supports the instrument
        bool verify_instrument(int instrument_num){
            // returns false if instrument_num is out of range
            if(instrument_num < 0 || instrument_num >127){
                return false;
            }
            return instruments[instrument_num];
        }
        // outputs all of the supported instruments
        void display_instruments(){
            // array of the category of instruments
            const std::string instrument_category[16] = {"Pianos", "Chromatic Percussion", "Organ", "Guitar", "Bass", "Strings", "Wind", "Flute", "Synth Lead", "Synth Pad", "Synth Effects", "Ethnic", "Percussive", "Drum & Percussion", "Sound Effects", "Miscellaneous"};
            int category_index = 0;
            for (int i = 0; i < 128; i++){
                // displays the next category
                if (category_index % 8 == 0){
                    std::cout << instrument_category[category_index] << std::endl;
                    category_index++;
                }
                // display supported instrument
                if(instruments[i] == true){
                    std::cout << i << ":\t" << smf::MidiFile::getGMInstrumentName(i)<<std::endl;
                }
            }
        }
};