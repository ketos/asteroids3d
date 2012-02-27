#include "io/SoundManager.hpp"

Sound* SoundManager::fire = 0;
Sound* SoundManager::explosion = 0;
Sound* SoundManager::menu = 0;
Sound* SoundManager::battle = 0;
Sound* SoundManager::warning = 0;

void SoundManager::playFireSound()
{
    if(fire == 0)
        fire = new Sound(1,"res/sounds/fire.wav");
    fire->playWAV(0); 
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
        menu = new Sound("res/sounds/menu.mp3");
    menu->playMP3();
}

void SoundManager::stopMenuSound()
{
    if(menu != 0)
        menu->stopMP3();
}

void SoundManager::playBattleMusic()
{
    if(battle == 0)
        battle = new Sound("res/sounds/battle.mp3");
    battle->playMP3();
}

void SoundManager::stopBattleMusic()
{
    if(battle != 0)
        battle->stopMP3();
}

void SoundManager::playWarningSound()
{
    if(warning == 0)
        warning = new Sound(2,"res/sounds/warning.wav");
    warning->playWAV(-1);
}

void SoundManager::stopWarningSound()
{
     if(warning != 0)
        warning->stopWAV();
}

void SoundManager::deleteManager()
{
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
