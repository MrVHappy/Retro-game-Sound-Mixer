// references: 
// https://www.fluidsynth.org/wiki/api/examples/example/
// https://www.fluidsynth.org/api/MIDIPlayer.html
// 

#include <fluidsynth.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <list>

#if defined(_WIN32)
#include <windows.h>
#define sleep(_t) Sleep(_t * 1000)

#include <process.h>
#define getpid _getpid

#define MEGA_DRIVE "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/sound_fonts/Mega-Drive/The_Ultimate Megadrive_Soundfont.sf2"
#define NES "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/sound_fonts/NES/8bitsf.SF2"
#define SNES "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/sound_fonts/SNES/SuperNintendoEntertainmentSystemV1.2.sf2"

#define EXAMPLE_MIDI "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/Demo Midis/Video Game/bubble-crab-s-stage.mid"
#else
#include <stdlib.h>
#include <unistd.h>
#endif


int main() {

    std::string file;
    std::string sound_font_file;
    std::cout << "Please enter file location of MIDI file" << std::endl;
    std::getline(std::cin, file);
    std::cout << "Please enter file location of sound font file" << std::endl;
    std::getline(std::cin, sound_font_file);
    fluid_settings_t* settings = NULL;
    fluid_synth_t* synth = NULL;
    fluid_audio_driver_t* adriver = NULL;
    fluid_player_t* player = NULL;
    std::list<int> sequence;
    int sfont_ID, i, key;
    int option = 4;
    std::string input;
    const char* FONT_TYPE = nullptr;
            
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

    sfont_ID = fluid_synth_sfload(synth,sound_font_file.c_str(), 1);

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

    // create the player
    player = new_fluid_player(synth);
    if (player == NULL){
        puts("Failed to create player");
        goto err;
    }

    fluid_player_add(player, file.c_str());

    fluid_player_play(player);
    fluid_player_join(player);
    
err:

    if (adriver != NULL) {
        delete_fluid_audio_driver(adriver);
    }
    if (synth != NULL) {
        delete_fluid_synth(synth);
    }
    if (settings != NULL) {
        delete_fluid_settings(settings);
    }
    if (player != NULL) {
        delete_fluid_player(player);
    }
    return 0;
}