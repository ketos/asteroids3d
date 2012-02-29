#include "rendering/partikel/Partikel-Flug.hpp"
#include <QtOpenGL>
#include <iostream>
#include "logic/Game.hpp"

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

    /*
    glEnable ( GL_RGBA_MODE ) ;
    glDisable ( GL_LIGHTING ) ;
    glBegin(GL_POINTS); //starts drawing of points
        glColor4f(1.0f,0.0f,0.0f,0.5f);
        glVertex3f(m_position[0], m_position[1], m_position[2]);
        //glVertex3f(0,0,0);
    glEnd();//end drawing of points
    glEnable ( GL_LIGHTING ) ;
    glDisable ( GL_RGBA_MODE ) ;
    */

    glVector<float> side = Game::getFighter()->getSide();
    side.normalize();
    glVector<float> up = Game::getFighter()->getUp();
    up.normalize();

    glVector<float> vec1 = m_position + side * 30;
    glVector<float> vec2 = m_position + up * 30;
    glVector<float> vec3 = m_position + side *30 + up * 30;

    
    glEnable ( GL_RGBA_MODE ) ;
    glDisable ( GL_LIGHTING ) ;
    glBegin(GL_QUADS); //starts drawing of points
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(m_position[0], m_position[1], m_position[2]);
        glVertex3f(vec1[0], vec1[1], vec1[2]);
        glVertex3f(vec3[0], vec3[1], vec3[2]);
        glVertex3f(vec2[0], vec2[1], vec2[2]);
        //glVertex3f(0,0,0);
    glEnd();//end drawing of points
    glEnable ( GL_LIGHTING ) ;
    glDisable ( GL_RGBA_MODE ) ;
}
