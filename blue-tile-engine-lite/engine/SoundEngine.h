#pragma once
#include <AL/al.h>
#include <AL/alc.h>

class SoundEngine {
public:
    //Default constructor
    SoundEngine(const char * path);

    //Deconstructor
    ~SoundEngine();

    ALCdevice * m_device;

    ALCcontext * m_context;

    ALfloat * listenerOri;

    ALuint m_bufferID;

    ALuint m_format;

    ALuint m_sourceID;
    int m_channel;
    int m_sampleRate;
    int m_bps;
    int m_size;

    char * m_data;
    bool isBigEndian();

    int convertToInt(char * buffer, int len);

    char * loadWAV(const char * f, int & chan, int & samplerate, int & bps, int & size);
};
