#include "rendering/partikel/Partikel-Explosion.hpp"
#include <iostream>
#include "logic/Game.hpp"
#include "io/TextureManager.hpp"

//Static Texture-Member
GLuint PartikelExplosion::TexID1 = 0;

PartikelExplosion::PartikelExplosion(glVector<float> pos, glVector<float> speed)
{
    m_lifetime  = 100;
    m_position  = pos;
    m_size      = 50;
    m_color     = glVector<float>(1,0,0); //White
    m_alive     = true;
    m_speed     = speed;
}

PartikelExplosion::~PartikelExplosion()
{

}

bool PartikelExplosion::isAlive()
{
    return m_alive;
}

void PartikelExplosion::update()
{
    //Update Lifetime
    m_lifetime--;
    if(!m_lifetime)
    {
        m_alive = false;
        return;
    }

    //Update Position
    m_position += m_speed;

    /*
    //Update Color
    //This Function expect as start Color 255,255,255
    if(m_color.z > 0)
    {
        m_color.z -= 0.01f;
    }
    else if (m_color.y > 0)
    {
        m_color.z = 0.0f;
        m_color.x -= 0.05f;
        m_color.y -= 0.05f;
    }
    else
    {
        m_color.y = 0.0f;
        m_color.z = 0.0f;
    }      

    //Update Speed
    m_speed = m_speed * 0.9f;
*/ 
}

void PartikelExplosion::render()
{
    glDisable ( GL_LIGHTING ) ;

    glBegin(GL_POINTS); //starts drawing of point
        glPointSize(m_size);
        glColor3f(m_color[0], m_color[1], m_color[2]);
        glVertex3f(m_position[0], m_position[1], m_position[2]);
    glEnd();

    glEnable ( GL_LIGHTING ) ;
}
