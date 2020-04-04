#include "SoundEngine.h"
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <fstream>
SoundEngine::SoundEngine(const char * path) {
    m_data = loadWAV(path, m_channel, m_sampleRate, m_bps, m_size);

    m_device = alcOpenDevice(NULL);

    if(m_device == NULL) {
        std::cout << "Cannot Open Sound Card" << std::endl;
    }

    m_context = alcCreateContext(m_device, NULL);
    if(m_context == NULL) {
        std::cout << "Cannot open context" << std::endl;
    }

    alcMakeContextCurrent(m_context);
   
    //Generate Buffers
    alGenBuffers(1, &m_bufferID);
    if(m_channel == 1) {
        if(m_bps == 8) {
            m_format = AL_FORMAT_MONO8;
        }else {
            m_format = AL_FORMAT_MONO16;
        }
    }else {
        if(m_bps == 8) {
            m_format = AL_FORMAT_STEREO8;
        }else {
            m_format = AL_FORMAT_STEREO16;
        }
    }
    alBufferData(m_bufferID, m_format, m_data, m_size, m_sampleRate);
    alGenSources(1, &m_sourceID);
    alSourcei(m_sourceID, AL_BUFFER, m_bufferID);
    alSourcePlay(m_sourceID); 
}

SoundEngine::~SoundEngine() {
    //Clean up
    alDeleteSources(1, &m_sourceID);
    alDeleteBuffers(1, &m_bufferID);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
    delete [] m_data;
}
//Checking the order of bytes.
//big-endian ordering places most significant byte first
bool SoundEngine::isBigEndian() {
    int a = 1;
    return !((char *)&a)[0];
}

int SoundEngine::convertToInt(char * buffer, int len) {
    int value = 0;

    if(!isBigEndian()) {
        for(int i = 0; i < len; i++)
            ((char*)&value)[i] = buffer[i];
    }else {
        for(int i = 0; i < len; i++) {
            ((char *)&value)[3 - i] = buffer[i];
        }
    }

    return value;
}

char * SoundEngine::loadWAV(const char * fn, int & chan, int & samplerate, int & bps, int & size) {
    char buffer[4];

    //Preparing I/O stream
    std::ifstream in(fn, std::ios::binary);
    in.read(buffer, 4);

    if(strncmp(buffer, "RIFF", 4) != 0) {
        std::cout << "Error not valid Wave" << std::endl;
        return NULL;
    }

    in.read(buffer, 4);
    in.read(buffer, 4);      //Wave
    in.read(buffer, 4);      //fmt
    in.read(buffer, 4);      //16
    in.read(buffer, 2);      //1
    in.read(buffer, 2);

    chan = convertToInt(buffer, 2);
    in.read(buffer, 4);
    samplerate = convertToInt(buffer, 4);
    in.read(buffer, 4);
    in.read(buffer, 2);
    in.read(buffer, 2);
    bps = convertToInt(buffer, 2);
    in.read(buffer, 4);
    in.read(buffer, 4);
    size = convertToInt(buffer, 4);
    
    char * data = new char[size];
    in.read(data, size);
    return data;
}

