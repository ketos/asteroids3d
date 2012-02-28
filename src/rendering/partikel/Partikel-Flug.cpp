#include "rendering/partikel/Partikel-Flug.hpp"
#include <QtOpenGL>


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

PartikelFlug::~PartikelFlug()
{

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
     glPointSize(20.0f);
     glEnable(GL_POINT_SMOOTH);
     glBegin(GL_POINTS);
     glColor3d(255,0,0);
     glVertex3d (m_position[0], m_position[1], m_position[2]);
     glEnd();
     glDisable(GL_POINT_SMOOTH);
}