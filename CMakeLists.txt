cmake_minimum_required(VERSION 3.20)

project(RetroSoundMixer)

set(CMAKE_CXX_STANDARD 17)

find_package(FluidSynth CONFIG REQUIRED)

add_subdirectory(midifile)

add_executable(RetroSoundMixer
    src/main.cpp
)

target_include_directories(RetroSoundMixer PRIVATE
    midifile/include
)

target_link_libraries(RetroSoundMixer PRIVATE
    midifile
    FluidSynth::libfluidsynth
)