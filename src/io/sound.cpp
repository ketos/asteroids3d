#include "io/sound.hpp"
Sound::Sound() {}
Sound::~Sound() {}

void Sound::playWAV(const char *wav){
    Mix_Chunk *music;
    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
    music = Mix_LoadWAV(wav);
    Mix_PlayChannel(1,music,0);
}
 
void Sound::playMP3(const char *mp3){
    Mix_Music *music;
    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
    music = Mix_LoadMUS(mp3);
    Mix_VolumeMusic(100);
    Mix_PlayMusic(music,-1);
}
