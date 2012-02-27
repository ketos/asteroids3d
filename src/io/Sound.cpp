#include "io/Sound.hpp"


Sound::Sound(int c, const char *wav) 
{
    Channel = c;
    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
    sound = Mix_LoadWAV(wav);
    music = 0;
}

Sound::Sound(const char* file)
{
    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
    music = Mix_LoadMUS(file);
    sound = 0;
}

Sound::~Sound() 
{
    if(music)
    {
        Mix_FreeMusic(music);
        music = NULL;
        //delete music;
    }
    if(sound)
    {
        Mix_FreeChunk(sound);
        sound = NULL;
        //delete sound;
    }
}

void Sound::playWAV(int loop)
{
    if(sound != 0)
        Mix_PlayChannel(Channel,sound,loop);
}
 
void Sound::playMP3(){
    //Mix_VolumeMusic(100);
    if(music != 0)
        Mix_FadeInMusic(music,-1,100);
}

void Sound::stopMP3()
{
    if(Mix_PlayingMusic())
        Mix_FadeOutMusic(1500);
}
