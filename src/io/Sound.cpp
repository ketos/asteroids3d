#include "io/Sound.hpp"
Sound::Sound(int c, const char *wav) 
{
    Channel = c;
    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
    sound = Mix_LoadWAV(wav);
}

Sound::Sound(const char* file)
{
    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
    music = Mix_LoadMUS(file);
}

Sound::~Sound() 
{
    if(music != 0)
        delete music;
    if(sound != 0)
        delete sound;
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
        Mix_FadeOutMusic(2000);
}
