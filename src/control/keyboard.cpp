#include "control/keyboard.hpp"
#include "logic/Game.hpp"
#include "view/RenderFrame.hpp"
#include <iostream>

std::set<int> Keyboard::m_pressedKeys;

void Keyboard::keypressed(QKeyEvent *event)
{
    m_pressedKeys.insert(event->key());
}

void Keyboard::keyrelease(QKeyEvent *event)
{
    m_pressedKeys.erase(event->key());
}
void Keyboard::update() 
{    
    if(Game::getFighter())
    {
    	// Controller for moving and rotation
    	if (m_pressedKeys.find(Qt::Key_W) != m_pressedKeys.end())
    	{
            //Game::getFighter()->move(STRAFE, -f_speed);
            (static_cast<Fighter*>(Game::getFighter()))->changeSpeed(1);
    	}

    	if (m_pressedKeys.find(Qt::Key_S) != m_pressedKeys.end())
    	{
            //Game::getFighter()->move(STRAFE, f_speed);
            (static_cast<Fighter*>(Game::getFighter()))->changeSpeed(-1);
    	}

    	if (m_pressedKeys.find(Qt::Key_Up) != m_pressedKeys.end())
    	{
            Game::getFighter()->rotate(PITCH, ANGLE);
    	}

    	if (m_pressedKeys.find(Qt::Key_Down) != m_pressedKeys.end())
    	{
            Game::getFighter()->rotate(PITCH, -ANGLE);
    	}

    	if (m_pressedKeys.find(Qt::Key_Left) != m_pressedKeys.end())
    	{
            Game::getFighter()->rotate(YAW,  ANGLE);
            Game::getFighter()->rotate(ROLL ,ANGLE);
    	}

    	if (m_pressedKeys.find(Qt::Key_Right) != m_pressedKeys.end())
    	{
            Game::getFighter()->rotate(YAW, -ANGLE);
            Game::getFighter()->rotate(ROLL ,-ANGLE);
    	}
    	// Schießen !!
    	if (m_pressedKeys.find(Qt::Key_Space) != m_pressedKeys.end())
    	{
            if(RenderFrame::shoot) {
    		    (static_cast<Fighter*>(Game::getFighter()))->shoot();
                RenderFrame::shoot = false;
            }
      	}
        // Ändern der Kamera
        if (m_pressedKeys.find(Qt::Key_PageUp) != m_pressedKeys.end())
        {
            RenderFrame::m_cam.zoom(-15);
        }
        if (m_pressedKeys.find(Qt::Key_PageDown) != m_pressedKeys.end())
        {
            RenderFrame::m_cam.zoom(15);
        } 
        if (m_pressedKeys.find(Qt::Key_9) != m_pressedKeys.end())
        {
            RenderFrame::m_cam.changeheight(5);
        }    
        if (m_pressedKeys.find(Qt::Key_0) != m_pressedKeys.end())
        {
            RenderFrame::m_cam.changeheight(-5);
        }
        //nicht löschen
        if (m_pressedKeys.find(Qt::Key_1) != m_pressedKeys.end())
        {
            RenderFrame::m_cam.setEgo();
            Game::setView(1);
            //Cockpit löschen
            if (Game::getHud())
            {
            	Game::getHud()->deleteCockpit();	
            }
        }
        if (m_pressedKeys.find(Qt::Key_2) != m_pressedKeys.end())   
        {
            RenderFrame::m_cam.setThird();
            Game::setView(2);
            //Cockpit löschen
            if (Game::getHud())
            {
            	Game::getHud()->deleteCockpit();	
            }
        }
        if (m_pressedKeys.find(Qt::Key_3) != m_pressedKeys.end())   
        {
            RenderFrame::m_cam.setCockpit();
            Game::setView(0);
            //Cockpit setzen
			if (Game::getHud())
         {
         	Game::getHud()->loadCockpit();	
         }
         
         
        }
    }
}

