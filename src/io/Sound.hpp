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
    /*
    *   Constructor for loading a wave-file and a Channel.
    *   @param int c The Audio-Channel
    *   @param const char* wav The Wave-File
    */
    Sound(int c, const char *wav);
    
    /*
    *   Constructor to load an mp3-file.
    *   @param const char* file The Mp3-File
    */
    Sound(const char* file);
    
    /*
    *   Default Destructor
    */
    ~Sound();
    
    /*
    *   Plays the wave-file on given Channel loop + 1 times
    */
    void playWAV(int loop);
    
    void stopWAV();
    
    /*
    *   Plays the mp3-file unlimited times.
    */
    void playMP3();
    
    /*
    *   Stops the mp3-file.
    */
    void stopMP3();
    
private:
    /*
    *   The Audio-Channel
    */
    int Channel;
    
    /*
    *   Mix_Chunk is needed to play wave-file on given Channel.
    */
    Mix_Chunk* sound;
    
    /*
    *   Mix_Music is needed to play mp3-file.
    */
    Mix_Music* music; 
};

#endif //_SOUND_H
