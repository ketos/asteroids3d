#include "io/Sound.hpp"
Sound::Sound(int c, const char *wav) 
{
    Channel = c;
    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
    music = Mix_LoadWAV(wav);
}
Sound::~Sound() 
{
    delete music;
}

void Sound::playWAV(int loop)
{
    Mix_PlayChannel(Channel,music,loop);
}
 
void Sound::playMP3(const char *mp3){
    Mix_Music *music;
    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
    music = Mix_LoadMUS(mp3);
    Mix_VolumeMusic(100);
    Mix_PlayMusic(music,-1);
    //Mix_PlayChannel(Channel,music,0);
}
