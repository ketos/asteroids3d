/**
*   @file SoundManager.cpp
*   @author gruppe3
*/

#include "io/SoundManager.hpp"

//init of all static members
Sound* SoundManager::fire = 0;
Sound* SoundManager::explosion = 0;
Sound* SoundManager::menu = 0;
Sound* SoundManager::battle = 0;
Sound* SoundManager::warning = 0;

void SoundManager::playFireSound()
{
    //create new firesound if its not exists
    if(fire == 0)
        fire = new Sound(1,"res/sounds/fire.wav");

    //play the sound
    fire->playWAV(0); 
}

void SoundManager::playExplosion()
{
    //create new explosionsound if its not exists
    if(explosion == 0)
        explosion = new Sound(3,"res/sounds/explo.wav");

    //play the sound
    explosion->playWAV(0); 
}

void SoundManager::playMenuSound()
{
    //create new menumusic if its not exists
    if(menu == 0)
        menu = new Sound("res/sounds/menu.mp3");

    //play the music
    menu->playMP3();
}

void SoundManager::stopMenuSound()
{
    //if menu exists stop it
    if(menu != 0)
        menu->stopMP3();
}

void SoundManager::playBattleMusic()
{
    //create new battlemusic if its not exists
    if(battle == 0)
        battle = new Sound("res/sounds/battle.mp3");

    //play the music
    battle->playMP3();
}

void SoundManager::stopBattleMusic()
{
    //if battle exists stop it
    if(battle != 0)
        battle->stopMP3();
}

void SoundManager::playWarningSound()
{
    //create new warningsound if its not exists
    if(warning == 0)
        warning = new Sound(2,"res/sounds/warning.wav");

    //play the sound unlimited times
    warning->playWAV(-1);
}

void SoundManager::stopWarningSound()
{
    //if warning exists stop it
    if(warning != 0)
        warning->stopWAV();
}

void SoundManager::deleteManager()
{
    //delete all sounds and music
    if(explosion)
        delete explosion;
    if(menu)
        delete menu;
    if(fire)
        delete fire;
    if(battle)
        delete battle;
    if(warning)
        delete warning;
}
