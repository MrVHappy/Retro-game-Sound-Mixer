// references: 
// https://www.fluidsynth.org/wiki/api/examples/example/
// https://www.fluidsynth.org/api/MIDIPlayer.html
// 

#include <fluidsynth.h>
#include <MidiFile.h>
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

void view_midi_info(const std::string file){
    // reads the MIDI file and extracts information about the tracks, events, and timing
    smf::MidiFile midi_file;
    // checks to see if the file was read successfully, if not print an error message and return
    if(!midi_file.read(file)){
        std::cout << "Failed to read MIDI file! Check the file path and try again." << std::endl;
        return;
    }
    // retrieving information of the number of tracks and ticks per quarter note in the MIDI file
    int num_tracks = midi_file.getTrackCount();

    std::cout << "Here are the number of tracks: " << num_tracks << std::endl;
    
    int num_tpq = midi_file.getTicksPerQuarterNote();
    std::cout << "Here are the ticks per quarter note: " << num_tpq << std::endl;

    // converting the file to absolute ticks
    // making it easier to calculate timings
    midi_file.makeAbsoluteTicks();

    // analyzing timing

    // Perform time analysis to calculate real world timing
    // analysing the tempo events and calculates seconds for
    // each tick
    midi_file.doTimeAnalysis();

    double sec_duration = midi_file.getFileDurationInSeconds();
    std::cout << "Here is the duration of the MIDI file in seconds: " << sec_duration << std::endl;

    double quarter_duration = midi_file.getFileDurationInQuarters();
    std::cout << "Here is the duration of a quarter note in seconds: " <<quarter_duration << std::endl;

    int tick_duration = midi_file.getFileDurationInTicks();
    std::cout << "Here is the duration of the MIDI file in ticks: " << tick_duration << std::endl;

    // iterate through events and extract data

    int total_events = 0;
    int note_on_count = 0;
    int note_off_count = 0;
    int instrument_change_count = 0;


    // iterate through all the tracks in the file
    for (int track = 0; track < midi_file.getTrackCount(); track++){
        
        // get the event list for the track
        smf::MidiEventList& event_list = midi_file[track];

        // get the number of events in the track
        int event_count = event_list.getEventCount();
        total_events += event_count;

        std::cout << "Track " << track << " has " << event_count << " events." << std::endl;

        // iterate through the events in the track
        for (int i = 0; i < event_count; i++){
            // get the individual event
            const smf::MidiEvent& event = event_list[i];
            // check if its a note on event
            if (event.isNoteOn()){
                note_on_count++;

                int key_number = event.getKeyNumber();
                int velocity = event.getVelocity();
                int tick = event.tick;
                double seconds = event.seconds;

                // to avoid clutter only show first few
                if (i < 3){
                    std::cout << "Note On event: key number = " << key_number << ", velocity = " << velocity << ", tick = " << tick << ", seconds = " << seconds << std::endl;

                }
            }
            else if (event.isNoteOff()){
                note_off_count++;
                int key_number = event.getKeyNumber();
                int ticks = event.tick;

                // only show first few
                if (i < 3){
                    std::cout << "Note Off event: key number = " << key_number << ", tick = " << ticks << std::endl;
                }
                
            }
            else if (event.isPatchChange()){
                int instrument = event.getP1();
                int tick = event.tick;

                instrument_change_count++;

                std::cout << "Instrument change event: instrument = " << instrument << ", tick = " << tick << std::endl;

            }
            

        }

    }

    std::cout << "Total number of events: " << total_events << std::endl;
    std::cout << "Total number of note on events: " << note_on_count << std::endl;
    std::cout << "Total number of note off events: " << note_off_count << std::endl;
    std::cout << "Total number of instrument change events: " << instrument_change_count << std::endl;
}

int main() {

    std::string file;
    std::string sound_font_file;
    std::cout << "Please enter file location of MIDI file" << std::endl;
    std::getline(std::cin, file);
    
    std::cout << "Would you like to view information about the MIDI file before playing? (y/n)" << std::endl;
    std::string view_info;
    std::getline(std::cin, view_info);
    if (view_info == "y" || view_info == "Y"){
        view_midi_info(file);
    }

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
        puts("Loading SoundFont failed! Check the file path and try again.");
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

    if (fluid_player_add(player, file.c_str()) != FLUID_OK) {
        puts("Failed to add MIDI file to player! Check the file path and try again.");
        goto err;
    }

    if (fluid_player_play(player) != FLUID_OK) {
        puts("Failed to play MIDI file");
        goto err;
    }
    fluid_player_join(player);
err:
    if (player != NULL) {
        delete_fluid_player(player);
    }
    if (adriver != NULL) {
        delete_fluid_audio_driver(adriver);
    }
    if (synth != NULL) {
        delete_fluid_synth(synth);
    }
    if (settings != NULL) {
        delete_fluid_settings(settings);
    }
    
    return 0;
}