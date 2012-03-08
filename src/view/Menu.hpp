/**
*   @file Menu.hpp
*   @author gruppe3
*/
#ifndef _MENU_H
#define _MENU_H

#include <QGLWidget>
#include "view/HUD.hpp"
#include "io/SoundManager.hpp"

class Menu {

    public:
        /**
         *@brief draws the splash
         *@param width width of the window
         *@param height height of the windows
         *@param h used hud
         */
        static void drawSplash(int width, int height, HUD* h);

        /**
         *@brief stop menu sound
         */
        static void deleteSplash();

        /**
         *@brief draws the Gameover screen
         *@param width width of the window
         *@param height height of the windows
         *@param h used hud
         */
        static void drawGameover(int width, int height, HUD* h);
        /**
         *@brief stop menu sound
         */
        static void deleteGameover();

};

#endif //_MENU_H
