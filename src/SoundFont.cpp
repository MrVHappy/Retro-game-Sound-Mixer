#include <map>
#include "fluidsynth.h"
#include <string>
#include <iostream>
#include <MidiFile.h>
#include "SoundFont.h"


        // constructor
        SoundFont::SoundFont(std::string file){
            this->file = file;
            
            // variables used for sound font analysis 
            fluid_settings_t* settings = new_fluid_settings();
            fluid_synth_t* synth = new_fluid_synth(settings);
            int sfont_ID = fluid_synth_sfload(synth,this->file.c_str(), 1);
            fluid_sfont_t* sfont = fluid_synth_get_sfont_by_id(synth,sfont_ID);

            // setup for instruments
            // loops through all the instruments
            for (int i = 0; i < 128; i++){
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
            clean_up(settings,synth);
        }
        // return the file location of the soundfont
        std::string SoundFont::get_file()const{
            return this->file;
        }
        // checks if the sound font supports the instrument
        bool SoundFont::verify_instrument(int instrument_num)const{
            // returns false if instrument_num is out of range
            if(instrument_num < 0 || instrument_num >127){
                return false;
            }
            return instruments.at(instrument_num);
        }
        // outputs all of the supported instruments
        void SoundFont::display_instruments(){
            // array of the category of instruments
            const std::string instrument_category[16] = {"Pianos", "Chromatic Percussion", "Organ", "Guitar", "Bass", "Strings", "Wind", "Flute", "Synth Lead", "Synth Pad", "Synth Effects", "Ethnic", "Percussive", "Drum & Percussion", "Sound Effects", "Miscellaneous"};
            int category_index = 0;
            for (int i = 0; i < 128; i++){
                // displays the next category
                if (i % 8 == 0){
                    std::cout << instrument_category[category_index] << std::endl;
                    category_index++;
                }
                // display supported instrument
                if(instruments[i] == true){
                    std::cout << i << ":\t" << smf::MidiFile::getGMInstrumentName(i)<<std::endl;
                }
            }
        }
        void SoundFont::clean_up(fluid_settings_t* settings,fluid_synth_t* synth){
            if (synth != NULL) {
                delete_fluid_synth(synth);
            }
            if (settings != NULL) {
                delete_fluid_settings(settings);
            }
            
        }
