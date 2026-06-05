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
    // while(true){
    //     std::cout << "Please select the following options: \n1.\tMega-drive/Genesis\n2.\tSNES \n3.\tNES" << std::endl;
    //     std::cin >> input;
    //     option = std::stoi(input);
        
    //     switch(option){
    //         case 1:
    //             FONT_TYPE = MEGA_DRIVE;
    //             break;
    //         case 2:
    //             FONT_TYPE = SNES;
    //             break;
    //         case 3:
    //             FONT_TYPE = NES;
    //             break;
    //         default:
    //             std::cout << "INVALID OPTION PLEASE CHOOSE AGAIN" << std::endl;
    //             continue;
    //         }
    //     break;
        
    // }
        
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
    // Seed random number generator
    srand(getpid());

    // Play random notes
    for (i = 0; i < 12; i++) {

        key = 60 + (int)(12.0f * rand() / (float)RAND_MAX);

        std::cout << "playing note:" << key << std::endl;

        fluid_synth_noteon(synth, 0, key, 80);

        sleep(1);

        fluid_synth_noteoff(synth, 0, key);
        
    }
    char note;
    bool exit = false;
    
    while (!exit){
        std::cout << "Please Play a note\n A(C),S(D),D(E),F(F),Q(EXIT)" << std::endl;
        std::cin >> note;
        switch(toupper(note)){
            case 'A':
                key = 60;
                sequence.push_back(key);
                break;
            case 'S':
                key = 62;
                break;
            case 'D':
                key = 64;
                break;
            case 'F':
                key = 65;
                break;
            case 'Q':
                exit = true;
                continue;
            default:
                continue;
            
        }
        sequence.push_back(key);
    }
    for (int seq : sequence){
        std::cout << seq << " ";
        fluid_synth_noteon(synth, 0, seq, 80);

        sleep(1);

        fluid_synth_noteoff(synth, 0, seq);
    }

err:

    delete_fluid_audio_driver(adriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
    delete_fluid_player(player);
    return 0;
}