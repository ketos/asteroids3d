#include "io/Sound.hpp"

Sound::Sound(int c, const char *wav) 
{
    //define Channel and Audio-Specs
    Channel = c;
    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);

    //load Wav-File into sound
    sound = Mix_LoadWAV(wav);

    //music not needed
    music = 0;
}

Sound::Sound(const char* file)
{
    //define Audio-Specs
    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);

    //Load Audio-File (mp3, wav, midi ..)
    music = Mix_LoadMUS(file);

    //sound and Channel not needed
    sound = 0;
    Channel = 0;
}

Sound::~Sound() 
{
    //destruct music or sound, only if exists
    if(music)
    {
        //deletes the music
        Mix_FreeMusic(music);
        music = NULL;
        //delete music;
    }
    if(sound)
    {
        //deletes the sound
        Mix_FreeChunk(sound);
        sound = NULL;
        //delete sound;
    }
}

void Sound::playWAV(int loop)
{
    //play sound on Channel only if sound exists
    if(sound)
        Mix_PlayChannel(Channel,sound,loop);
}

void Sound::stopWAV()
{
    //stop sound on Channel only if sound exists
    //and sound is playing
    if(sound && Mix_Playing(Channel))
        Mix_HaltChannel(Channel);
}
 
void Sound::playMP3(){
    //play music with fade in effect
    //only if music exists
    if(music != 0)
        Mix_FadeInMusic(music,-1,100);
}

void Sound::stopMP3()
{
    //stops music with fade out effect
    //only if music is playing
    if(Mix_PlayingMusic())
        Mix_FadeOutMusic(1500);
}
