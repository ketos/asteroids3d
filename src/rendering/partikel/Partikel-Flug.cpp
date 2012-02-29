#include "rendering/partikel/Partikel-Flug.hpp"
#include <QtOpenGL>
#include <iostream>

PartikelFlug::PartikelFlug(float lifetime,
                       glVector<float> pos,
                       float size, 
                       glVector<float> color)
{
    m_lifetime = lifetime;
    m_position = pos;
    m_size     = size;
    m_color    = color;
    m_alive = true;
}

bool PartikelFlug::isAlive()
{
    return m_alive;
}

void PartikelFlug::update()
{
    m_lifetime--;
    if(m_lifetime == 0)
    {
        m_alive = false;
    }
}

void PartikelFlug::render()
{
    //TODO render GLSphere
    
    
    glPointSize(10); //set point size to 10 pixels


   glDisable ( GL_LIGHTING ) ;
    glBegin(GL_POINTS); //starts drawing of points
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(m_position[0], m_position[1], m_position[2]);
        //glVertex3f(0,0,0);
    glEnd();//end drawing of points
       glEnable ( GL_LIGHTING ) ;
}
