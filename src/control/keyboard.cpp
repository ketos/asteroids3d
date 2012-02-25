#include "control/keyboard.hpp"
#include <iostream>
Keyboard::Keyboard(Fighter &mesh, Camera &cam, bool &shoot) : m_mesh(mesh), m_cam(cam)
{
    //m_pressedKeys = new std::set<int>();
    m_shoot = &shoot;
}

Keyboard::~Keyboard()
{
    delete m_pressedKeys;
}

void Keyboard::keypressed(QKeyEvent *event)
{
    m_pressedKeys->insert(event->key());
}

void Keyboard::keyrelease(QKeyEvent *event)
{
    m_pressedKeys->erase(event->key());
}
void Keyboard::update() 
{
    	// Controller for moving and rotation
    	if (m_pressedKeys->find(Qt::Key_W) != m_pressedKeys->end())
    	{
            m_mesh.changeSpeed(10);
    	}

    	if (m_pressedKeys->find(Qt::Key_S) != m_pressedKeys->end())
    	{
            m_mesh.changeSpeed(-SPEED);
    	}

    	if (m_pressedKeys->find(Qt::Key_Up) != m_pressedKeys->end())
    	{
            m_mesh.rotate(PITCH, ANGLE);
    	}

    	if (m_pressedKeys->find(Qt::Key_Down) != m_pressedKeys->end())
    	{
            m_mesh.rotate(PITCH, -ANGLE);
    	}

    	if (m_pressedKeys->find(Qt::Key_Left) != m_pressedKeys->end())
    	{
            m_mesh.rotate(YAW,  ANGLE);
    	}

    	if (m_pressedKeys->find(Qt::Key_Right) != m_pressedKeys->end())
    	{
            m_mesh.rotate(YAW, -ANGLE);
    	}
    	// Schießen !!
    	if (m_pressedKeys->find(Qt::Key_Space) != m_pressedKeys->end())
    	{
            if(m_shoot) {
    		    m_mesh.shoot();
                m_shoot = false;
                //m_timer2->start();
            }
      	}
        // Ändern der Kamera
        if (m_pressedKeys->find(Qt::Key_PageUp) != m_pressedKeys->end())
        {
            m_cam.zoom(-15);
        }
        if (m_pressedKeys->find(Qt::Key_PageDown) != m_pressedKeys->end())
        {
            m_cam.zoom(15);
        } 
        if (m_pressedKeys->find(Qt::Key_9) != m_pressedKeys->end())
        {
            m_cam.changeheight(5);
        }    
        if (m_pressedKeys->find(Qt::Key_0) != m_pressedKeys->end())
        {
            m_cam.changeheight(-5);
        }    
        if (m_pressedKeys->find(Qt::Key_O) != m_pressedKeys->end())
        {
            if(m_shoot) {
                m_shoot = false;
                //aenderModel("bearcat.3ds");
                //m_timer2->start();
            }  
        } 
}

