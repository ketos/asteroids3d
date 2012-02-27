#ifndef _SOUNDMANAGER_H
#define _SOUNDMANAGER_H

#include "io/Sound.hpp"

class SoundManager {

    public:
    /*
    *   Plays the fire-sound
    */
    static void playFireSound();
      
    /*
    *   Plays the explosions-sound
    */
    static void playExplosion();
    
    /*
    *   Plays the menu-sound
    */
    static void playMenuSound();
    
    /*
    *   stops the menu-sound
    */
    static void stopMenuSound();
    
    /*
    *   Plays the battle-sound
    */
    static void playBattleMusic();
    
    /*
    *   stops the battle-sound
    */
    static void stopBattleMusic();
    

    /*
    * Deletes all Mediafiles
    */
    static void deleteManager();
    
    private:
    static Sound* fire;
    static Sound* explosion;
    static Sound* menu;
    static Sound* battle;

};

#endif //_SOUNDMANAGER_H
