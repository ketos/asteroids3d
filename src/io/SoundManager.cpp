#include "io/SoundManager.hpp"

Sound* SoundManager::fire = 0;
Sound* SoundManager::background = 0;
Sound* SoundManager::explosion = 0;

void SoundManager::playFireSound()
{
    if(fire == 0)
        fire = new Sound(1,"sound.wav");
    fire->playWAV(); 
}

void SoundManager::playBackground()
{
    if(background == 0)
        background = new Sound(2,"bg.wav");
    background->playBackground(); 
}

void SoundManager::playExplosion()
{
    if(explosion == 0)
        explosion = new Sound(3,"explo.wav");
    explosion->playWAV(); 
}

void SoundManager::deleteManager()
{
    delete fire;
    delete background;
    delete explosion;
}
