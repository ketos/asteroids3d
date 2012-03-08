#include "view/Menu.hpp"

bool sound = false;

void Menu::drawSplash(int width, int height, HUD* h)
{   //draws the splash
    h->drawSplash(width, height);
    if(!sound)
    {
    	  //starts the sound if not already running
        SoundManager::playMenuSound();
        sound = true;    
    }
}
void Menu::drawGameover(int width, int height, HUD* h)
{
	 //draws Gameover screen
    h->drawGameover(width, height);
    if(!sound)
    {
    	  //starts sound if not already running	
        SoundManager::playMenuSound();
        sound = true;    
    }
}

void Menu::deleteSplash()
{
	 //stops the sound
	 sound = false;
    SoundManager::stopMenuSound();
}
void Menu::deleteGameover()
{
	 //stops the sound
	 sound = false;
    SoundManager::stopMenuSound();
}
