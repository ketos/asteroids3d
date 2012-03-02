/**
*   @file SoundManager.hpp
*   @author gruppe3
*/

#ifndef _SOUNDMANAGER_H
#define _SOUNDMANAGER_H

#include "io/Sound.hpp"

/**
*   @brief Die SoundManager Klasse organisiert alle Sounds und regelt deren ablauf
*/
class SoundManager {

    public:
    /**
    *   @brief Plays the fire-sound
    */
    static void playFireSound();
      
    /**
    *   @brief Plays the explosions-sound
    */
    static void playExplosion();
    
    /**
    *   @brief Plays the menu-sound
    */
    static void playMenuSound();
    
    /**
    *   @brief stops the menu-sound
    */
    static void stopMenuSound();
    
    /**
    *   @brief Plays the battle-sound
    */
    static void playBattleMusic();
    
    /**
    *   @brief stops the battle-sound
    */
    static void stopBattleMusic();
    
    /**
    *   @brief Plays the Warning-sound
    */
    static void playWarningSound();

    /**
    *   @brief stops the Warning-sound
    */
    static void stopWarningSound();

    /**
    *   @brief Deletes all Mediafiles
    */
    static void deleteManager();
    
    private:
    /**
    *   @brief The Firesound Member
    */
    static Sound* fire;

    /**
    *   @brief The Explosionsound Member
    */
    static Sound* explosion;

    /**
    *   @brief The Menusound Member  
    */
    static Sound* menu;

    /**
    *   @brief The Battlesound Member
    */
    static Sound* battle;

    /**
    *   @brief The Warningsound Member
    */
    static Sound* warning;

};

#endif //_SOUNDMANAGER_H
