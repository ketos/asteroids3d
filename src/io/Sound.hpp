#ifndef _SOUND_H
#define _SOUND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
 
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>


class Sound{
public:
    Sound(int c, const char *wav);
    Sound(const char* file);
    ~Sound();
    void playWAV(int loop);
    void playMP3();
private:
    int Channel;
    Mix_Chunk* sound;
    Mix_Music* music; 
};

#endif //_SOUND_H
