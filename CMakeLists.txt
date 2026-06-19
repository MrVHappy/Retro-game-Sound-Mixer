cmake_minimum_required(VERSION 3.20)

# Must be before project()
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(FluidSynth_DIR "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-windows/share/fluidsynth")

project(RetroSoundMixer)

set(CMAKE_CXX_STANDARD 17)

find_package(FluidSynth CONFIG REQUIRED)
find_package(SndFile CONFIG REQUIRED)
find_package(mp3lame CONFIG REQUIRED)

add_subdirectory(midifile)

add_executable(RetroSoundMixer
    src/main.cpp
)

target_include_directories(RetroSoundMixer PRIVATE
    midifile/include
)

target_link_libraries(RetroSoundMixer PRIVATE
    debug ${CMAKE_BINARY_DIR}/midifile/Debug/midifile.lib
    optimized ${CMAKE_BINARY_DIR}/midifile/Release/midifile.lib
    FluidSynth::libfluidsynth
    SndFile::sndfile
    mp3lame::mp3lame
)