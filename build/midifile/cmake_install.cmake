# Install script for directory: C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/midifile

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/RetroSoundMixer")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/build/midifile/Debug/midifile.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/build/midifile/Release/midifile.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/build/midifile/MinSizeRel/midifile.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/build/midifile/RelWithDebInfo/midifile.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/midifile" TYPE FILE FILES
    "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/midifile/include/Binasc.h"
    "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/midifile/include/MidiEvent.h"
    "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/midifile/include/MidiEventList.h"
    "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/midifile/include/MidiFile.h"
    "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/midifile/include/MidiMessage.h"
    "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/midifile/include/Options.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/Sebastian/OneDrive/Documents/GitHub/Retro-game-Sound-Mixer/build/midifile/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
