#include "view/Menu.hpp"

HUD* Menu::hins = 0;
bool sound = false;

void Menu::drawSplash(int width, int height, HUD* h)
{    
    h->drawSplash(width, height);
    if(!sound)
    {
        SoundManager::playMenuSound();
        sound = true;    
    }
}

void Menu::deleteSplash()
{
    SoundManager::stopMenuSound();
}