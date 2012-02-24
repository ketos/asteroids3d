#ifndef _MENU_H
#define _MENU_H

#include <QGLWidget>
#include "view/HUD.hpp"
#include "io/SoundManager.hpp"

class Menu {
    
    public:
        static void drawMenu(int width, int height, QPainter* p);
        static void deleteMenu();
        
    private:
        static HUD* hins;
          
};

#endif //_MENU_H