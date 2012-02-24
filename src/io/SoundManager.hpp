#ifndef _SOUNDMANAGER_H
#define _SOUNDMANAGER_H

#include "io/Sound.hpp"

class SoundManager {

    public:
    static void playFireSound();
    static void playBackground();
    static void playExplosion();
    static void playMenuSound();
    static void stopMenuSound();
    
    /*
    * Deletes all Mediafiles
    */
    static void deleteManager();
    
    private:
    static Sound* fire;
    static Sound* background;
    static Sound* explosion;
    static Sound* menu;

};

#endif //_SOUNDMANAGER_H
