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
    /**
    *   @brief Constructor for loading a wave-file and a Channel.
    *   @param int c The Audio-Channel
    *   @param const char* wav The Wave-File
    */
    Sound(int c, const char *wav);
    
    /**
    *   @brief Constructor to load an mp3-file.
    *   @param const char* file The Mp3-File
    */
    Sound(const char* file);
    
    /**
    *   @brief Default Destructor
    */
    ~Sound();
    
    /**
    *   @brief Plays the wave-file on given Channel loop + 1 times
    */
    void playWAV(int loop);
    
    /**
    *   @brief Stops the wave-file
    */
    void stopWAV();
    
    /*
    *   @brief Plays the mp3-file unlimited times.
    */
    void playMP3();
    
    /*
    *   @brief Stops the mp3-file.
    */
    void stopMP3();
    
private:
    /**
    *   @brief The Audio-Channel
    */
    int Channel;
    
    /**
    *   @brief Mix_Chunk is needed to play wave-file on given Channel.
    */
    Mix_Chunk* sound;
    
    /**
    *   @brief Mix_Music is needed to play mp3-file.
    */
    Mix_Music* music; 
};

#endif //_SOUND_H
