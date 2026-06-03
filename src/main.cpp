#include <fluidsynth.h>
#include <iostream>
#include <string>
#include <cstdlib>

#if defined(_WIN32)
#include <windows.h>
#define sleep(_t) Sleep(_t * 1000)

#include <process.h>
#define getpid _getpid

#define MEGA_DRIVE "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/sound_fonts/Mega-Drive/The_Ultimate Megadrive_Soundfont.sf2"
#define NES "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/sound_fonts/NES/8bitsf.SF2"
#define SNES "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/sound_fonts/SNES/SuperNintendoEntertainmentSystemV1.2.sf2"

#else
#include <stdlib.h>
#include <unistd.h>
#endif


int main() {

    fluid_settings_t* settings = NULL;
    fluid_synth_t* synth = NULL;
    fluid_audio_driver_t* adriver = NULL;

    int sfont_ID, i, key;
    int option = 4;
    std::string input;
    const char* FONT_TYPE = nullptr;
    while(true){
        std::cout << "Please select the following options: \n1.\tMega-drive/Genesis\n2.\tSNES \n3.\tNES" << std::endl;
        std::cin >> input;
        option = std::stoi(input);
        
        switch(option){
            case 1:
                FONT_TYPE = MEGA_DRIVE;
                break;
            case 2:
                FONT_TYPE = SNES;
                break;
            case 3:
                FONT_TYPE = NES;
                break;
            default:
                std::cout << "INVALID OPTION PLEASE CHOOSE AGAIN" << std::endl;
                continue;
            }
        break;
        
        


    }
    

    
    // Create settings
    settings = new_fluid_settings();

    if (settings == NULL) {
        puts("settings creation failed");
        goto err;
    }

    // Create synth
    synth = new_fluid_synth(settings);

    if (synth == NULL) {
        puts("synth creation failed");
        goto err;
    }

    // Load SoundFont
    std::cout << "Loading SF2..." << std::endl;

    sfont_ID = fluid_synth_sfload(synth,FONT_TYPE, 1);

    if (sfont_ID == FLUID_FAILED) {
        puts("Loading SoundFont failed!");
        goto err;
    }

    // Create audio driver
    adriver = new_fluid_audio_driver(settings, synth);

    if (adriver == NULL) {
        puts("Failed to create audio driver");
        goto err;
    }

    // Seed random number generator
    srand(getpid());

    // Play random notes
    for (i = 0; i < 12; i++) {

        key = 60 + (int)(12.0f * rand() / (float)RAND_MAX);

        fluid_synth_noteon(synth, 0, key, 80);

        sleep(1);

        fluid_synth_noteoff(synth, 0, key);
    }

err:

    delete_fluid_audio_driver(adriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);

    return 0;
}