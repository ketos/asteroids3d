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
    delete music;
}

void Sound::playWAV(int loop)
{
    if(sound != 0)
        Mix_PlayChannel(Channel,sound,loop);
}
 
void Sound::playMP3(){
    //Mix_VolumeMusic(100);
    if(music != 0)
        Mix_PlayMusic(music,-1);
}
