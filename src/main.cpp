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
#include <map>

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

std::string midi_processing(const std::string file){
    // A constant value where the new file will be saved
    const std::string DESTINATION = "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/Saved songs/";
    // reads the midi file to and checks if the file exists
    smf::MidiFile midi_file;
    if(!midi_file.read(file)){
        std::cout << "ERROR:\tFailed to read MIDI file! Check the file path and try again." << std::endl;
        return "error";
    }
    // gets the number of tracks inside of the midi file
    int track_count = midi_file.getTrackCount();
    std::cout << "Number of tracks: " << track_count << std::endl;

    // checks if there is information in the midi file
    if (track_count <=0){
        std::cout << "ERROR:\tthere are no tracks in your midi file please select another file" << std::endl;
        return "error";
    }

    // for loop goes through every track and event in the song
    for (int track = 0; track < track_count; track++){
        // gets the number of events in the ith track
        int event_count = midi_file.getEventCount(track);
        // if there are no events in the track then skip 
        if(event_count <= 0){
            continue;
        }
        // else go through each event
        for(int event = 0; event < event_count; event++){
            // analyse the current event
            smf::MidiEvent& current_event = midi_file[track][event];
            // skip if the event is empty
            if(current_event.isEmpty()){
                continue;
            }
            // check if there is a change of instrument
            if(current_event.isPatchChange()){
                // get the new instrument
                int current_instrument = current_event.getP1();
                // skip invalid instrument
                if(current_instrument < 0 || current_instrument >127){
                    continue;
                }
                // get the channel of the instrument
                int channel = current_event.getChannelNibble();
                // skip if the channel is not valid
                if (channel < 0 || channel > 15){
                    continue;
                }
                // get the instrument name
                std::string instrument_name = smf::MidiFile::getGMInstrumentName(current_instrument);
                
                // display the track and event information
                std::cout << "Track: " << track << std::endl;
                std::cout << "Channel: " << channel << std::endl;
                std::cout << "Current Instrument: " << current_instrument << std::endl;
                std::cout << "Current Instrument Name: " << instrument_name << std::endl;
                
                // promt user if they would like to change the instrument
                std::string option;
                std::cout << "Would you like to chnage instrument (y/n)" << std::endl;
                std::cin >> option;

                // if yes then allow the user to select a new instrument
                if (option == "y" || option == "Y"){
                    std:: cout << "0-127 avalable" << std::endl;
                
                    int new_instrument;
                    std::cout << "Enter new instrument Number" << std::endl;
                    std::cin >> new_instrument;
                    // check to see if the instrument number is valid
                    if(new_instrument < 0 || new_instrument >127){
                        std::cout << "Number out of range skiping" << std::endl;
                        continue;
                    }
                    // display the name of the new instrument
                    std::string new_name = smf::MidiFile::getGMInstrumentName(new_instrument);
                    std::cout << "New Instrument name: " << new_name << std::endl;
                    
                    // change the instrument
                    current_event.setP1(new_instrument);

                    std::cout << "Instrument has Changed successfully" << std::endl;
                }
            }
        }
    }
    // sorting tracks
    std::cout << "Sorting tracks" << std::endl;
    midi_file.sortTracks();
    std::cout << "Sorting tracks complete" << std::endl;

    // ask user to type in the new song name
    std::string file_name;
    std::cout << "Please enter file name:" << std::endl;
    std:: cin >> file_name;
    // assigns it to a path
    file_name = DESTINATION + file_name + ".midi";
    // saves the foile
    std::cout << "saving..." << std::endl;
    if(midi_file.write(file_name)){
        std::cout << "File Saved at location: " << file_name << std::endl;
    }
    else{
        std::cout << "Failed to Save file" << std:: endl;
    }
    return file_name;
}

void display_instruments(){
    // array of all the types of instruments
    const std::string instrument_category[16] = {"Pianos", "Chromatic Percussion", "Organ", "Guitar", "Bass", "Strings", "Wind", "Flute", "Synth Lead", "Synth Pad", "Synth Effects", "Ethnic", "Percussive", "Drum & Percussion", "Sound Effects", "Miscellaneous"};
    int category_index = 0;
    
    std::string current_instrument;
    std::string prev_instrument;
    int start = 0;
    int end;
    // loop through all the instruments
    for (int i = 0; i < 128; i++){
        // displays the next instrument category
        if (i % 8 == 0){
            std::cout << instrument_category[category_index] << std::endl;
            category_index++;
        }
        // gets the instrument index and name
        end = i;
        current_instrument = smf::MidiFile::getGMInstrumentName(i);
        // skip first
        if(i == 0){
            continue;
        }
        // output last
        if (i == 127){
            std::cout << "\t" << current_instrument << " "<< end << std::endl; 
            break;
        }
        // check if the last instrument is the same as the current
        prev_instrument = smf::MidiFile::getGMInstrumentName(i -1);
        if(current_instrument != prev_instrument){
            std::cout << "\t" << current_instrument << " " << end << std::endl;
            start = i;
        }
    }
}


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
    // displays the instruments
    display_instruments();
    std::string file;
    std::string sound_font_file;
    // promts user to enter file location of midi and sound font file
    std::cout << "Please enter file location of MIDI file" << std::endl;
    std::getline(std::cin, file);
    std::cout << "Please enter file location of sound font file" << std::endl;
    std::getline(std::cin,sound_font_file);
    
    // asks user if they would like to see midi file information
    std::cout << "Would you like to view information about the MIDI file before playing? (y/n)" << std::endl;
    std::string view_info;
    std::getline(std::cin, view_info);
    if (view_info == "y" || view_info == "Y"){
        // display file information if typed yes
        view_midi_info(file);
        
    }

    // modifies the midi file
    file = midi_processing(file);
    // displays new file location
    std::cout << file << std::endl;
    
    // setting up midi player
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
    // checks to see if the settings has been created successfully
    if (settings == NULL) {
        puts("settings creation failed");
        goto err;
    }

    // Create synth
    synth = new_fluid_synth(settings);
    // checks to see if the synth has been created successfully
    if (synth == NULL) {
        puts("synth creation failed");
        goto err;
    }

    // Load SoundFont
    std::cout << "Loading SF2..." << std::endl;

    sfont_ID = fluid_synth_sfload(synth,sound_font_file.c_str(), 1);
    // checks to see if the sound font has been created successfully
    if (sfont_ID == FLUID_FAILED) {
        puts("Loading SoundFont failed! Check the file path and try again.");
        goto err;
    }

    // Create audio driver
    adriver = new_fluid_audio_driver(settings, synth);
    // checks to see if the audio driver has been created successfully
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
// clean up
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