#ifndef _MENU_H
#define _MENU_H

#include <QGLWidget>
#include "view/HUD.hpp"
#include "io/SoundManager.hpp"

class Menu {
    
    public:
        static void drawSplash(int width, int height, HUD* h);
        static void deleteSplash();
        static void drawMenu();
        
    private:
        static HUD* hins;
          
};

#endif //_MENU_H