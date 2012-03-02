/**
 * @file keyboard.cpp
 *
 * @author gruppe3
 */

#include "control/keyboard.hpp"
#include "logic/Game.hpp"
#include "view/RenderFrame.hpp"
#include <iostream>
#include "math/Global.hpp"
#include "control/control.hpp"

//Liste mit den Tasten
std::set<int> Keyboard::m_pressedKeys;

void Keyboard::keypressed(QKeyEvent *event)
{
    // Fügt die Taste in die Liste ein
    m_pressedKeys.insert(event->key());
}

void Keyboard::keyrelease(QKeyEvent *event)
{
    // löscht die Taste aus der Liste
    m_pressedKeys.erase(event->key());
}
void Keyboard::update() 
{    
    // wenn ein Fighter vorhanden ist
    if(Game::getFighter())
    {
        // Wenn eine Taste in der Liste vorhanen führe die passende Aktion aus
        // W - Beschleunigen
    	if (m_pressedKeys.find(Qt::Key_W) != m_pressedKeys.end())
    	{
            Game::getFighter()->changeSpeed(1);
    	}
        // S - Bremsen
    	if (m_pressedKeys.find(Qt::Key_S) != m_pressedKeys.end())
    	{
            Game::getFighter()->changeSpeed(-1);
    	}
        // Pfeil hoch - Spitze nach oben
    	if (m_pressedKeys.find(Qt::Key_Up) != m_pressedKeys.end())
    	{
            Game::getFighter()->changeAngle(PITCH, ANGLE);
    	}
        // Pfeil runter - Spitze nach unten
    	if (m_pressedKeys.find(Qt::Key_Down) != m_pressedKeys.end())
    	{
            Game::getFighter()->changeAngle(PITCH, -ANGLE);
    	}
        // Pfeil links - nach Links
    	if (m_pressedKeys.find(Qt::Key_Left) != m_pressedKeys.end())
    	{
            Game::getFighter()->changeAngle(YAW  , ANGLE);
            Game::getFighter()->changeAngle(ROLL , ANGLE);
    	}
        // Pfeil rechts - nach Rechts
    	if (m_pressedKeys.find(Qt::Key_Right) != m_pressedKeys.end())
    	{
            Game::getFighter()->changeAngle(YAW  ,-ANGLE);
            Game::getFighter()->changeAngle(ROLL ,-ANGLE);
    	}
    	// Space - schiessen
    	if (m_pressedKeys.find(Qt::Key_Space) != m_pressedKeys.end())
    	{
            if(Game::getshoot()) {    
    		    Game::getFighter()->shoot();
                Game::shot();
            }
      	}
        // PageUp - Kamera ranholen
        if (m_pressedKeys.find(Qt::Key_PageUp) != m_pressedKeys.end())
        {
            RenderFrame::m_cam.zoom(-15);
        }
        // PageDown - Kamera entfernen
        if (m_pressedKeys.find(Qt::Key_PageDown) != m_pressedKeys.end())
        {
            RenderFrame::m_cam.zoom(15);
        }
        // 9 - Kamerahoehe ändern
        if (m_pressedKeys.find(Qt::Key_9) != m_pressedKeys.end())
        {
            RenderFrame::m_cam.changeheight(5);
        }
        // 0 - Kamerahoehe ändern    
        if (m_pressedKeys.find(Qt::Key_0) != m_pressedKeys.end())
        {
            RenderFrame::m_cam.changeheight(-5);
        }
        // 1 - First-Person-Ansicht
        if (m_pressedKeys.find(Qt::Key_1) != m_pressedKeys.end())
        {
            RenderFrame::m_cam.setEgo();
            Game::setView(1);
            //kein Cockpit zeichnen
            if (Game::getHud())
            {
            	Game::getHud()->deleteCockpit();	
            }
        }
        // 2 - Third-Person-Ansicht
        if (m_pressedKeys.find(Qt::Key_2) != m_pressedKeys.end())   
        {
            RenderFrame::m_cam.setThird();
            Game::setView(2);
            //kein Cockpit zeichnen
            if (Game::getHud())
            {
            	Game::getHud()->deleteCockpit();	
            }
        }
        // 3 - Cockpitansicht
        if (m_pressedKeys.find(Qt::Key_3) != m_pressedKeys.end())   
        {
            RenderFrame::m_cam.setCockpit();
            Game::setView(0);
            //Cockpit zeichen
            if (Game::getHud())
            {
         	    Game::getHud()->loadCockpit();	
            }
        }
        // Escape - Alle Bewegungen auf 0
        if (m_pressedKeys.find(Qt::Key_Escape) != m_pressedKeys.end())
        {
            Game::getFighter()->setNULL();
        }
    }
}

