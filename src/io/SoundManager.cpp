#include "io/SoundManager.hpp"

Sound* SoundManager::fire = 0;
Sound* SoundManager::background = 0;
Sound* SoundManager::explosion = 0;
Sound* SoundManager::menu = 0;

void SoundManager::playFireSound()
{
    if(fire == 0)
        fire = new Sound(1,"res/sounds/fire.wav");
    fire->playWAV(0); 
}

void SoundManager::playBackground()
{
    if(background == 0)
        background = new Sound(2,"res/sounds/bg.wav");
    background->playWAV(-1); 
}

void SoundManager::playExplosion()
{
    if(explosion == 0)
        explosion = new Sound(3,"res/sounds/explo.wav");
    explosion->playWAV(0); 
}

void SoundManager::playMenuSound()
{
    if(menu == 0)
        menu = new Sound(2,"res/sounds/menu.wav");
    menu->playWAV(-1);
    
}

void SoundManager::stopMenuSound()
{
    Mix_ExpireChannel(2,1);
    delete menu;
}

void SoundManager::deleteManager()
{
    delete fire;
    delete background;
    delete explosion;
    delete menu;
}
