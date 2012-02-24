#include "view/Menu.hpp"

HUD* Menu::hins = 0;
bool sound = false;

void Menu::drawMenu(int width, int height, QPainter* p)
{    
    if(hins == 0)
        hins = new HUD();
        
    hins->drawSplash(width, height, p);
    if(!sound)
    {
        SoundManager::playMenuSound();
        sound = true;    
    }
}

void Menu::deleteMenu()
{
    SoundManager::stopMenuSound();
}