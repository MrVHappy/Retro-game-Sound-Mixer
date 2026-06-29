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

class Encoder{
    private:
        char* file_location;
        const char* MP3_LOC = "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/MP3/example.mp3";
        

    public:
        Encoder(char* file_location){
            this->file_location = file_location;
        }
        void wav2mp3(){
            // the buffer size for each samples
            const short BUFFER_SIZE = 8192;
            // static short int data[BUFFER_SIZE];
            int read_count;
            SF_INFO info;
            memset(&info,0, sizeof(info));
            // opens the wav file and sets to read
            SNDFILE *file = sf_open(this->file_location,SFM_READ,&info);
            // sets a file to be written to 
            FILE *output = fopen(MP3_LOC,"wb");
            
            // checks to see if the file has been extracted successfully
            if (file == NULL){
                std::cout << "ERROR: Unable to Open file" << std::endl;
                return;
            }
            if (output == NULL){
                std::cout << "ERROR: Unable to Open file" << std::endl;
                return;
            }
            static std::vector<short int> data;
            data.resize(BUFFER_SIZE * info.channels);

            lame_t encoder = lame_init();
            int sample_rate = lame_set_in_samplerate(encoder,info.samplerate);
            int channel_count = lame_set_num_channels(encoder,info.channels);
            int bit_rate = lame_set_brate(encoder, 320);
            int quality = lame_set_quality(encoder,0);
            lame_init_params(encoder);

            // unsigned char* MP3_LOC_US = (unsigned char*) MP3_LOC;
            unsigned char MP3_BUFFER[BUFFER_SIZE * 4];
            
            while ((read_count = (int) sf_readf_short(file,data.data(),BUFFER_SIZE))){
                int Bytes = lame_encode_buffer_interleaved(encoder,data.data(),read_count,MP3_BUFFER,sizeof(MP3_BUFFER));
                fwrite(MP3_BUFFER,1,Bytes,output);
            }
            int flush_bytes = lame_encode_flush(encoder, MP3_BUFFER, sizeof(MP3_BUFFER));
            fwrite(MP3_BUFFER,1,flush_bytes,output);
            sf_close(file);
            fclose(output);
            lame_close(encoder);
    }
};