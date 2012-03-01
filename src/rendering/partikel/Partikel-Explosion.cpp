#include "rendering/partikel/Partikel-Explosion.hpp"
#include <iostream>
#include "logic/Game.hpp"
#include "io/TextureManager.hpp"

//Static Texture-Member
GLuint PartikelExplosion::TexID1 = 0;

PartikelExplosion::PartikelExplosion(float lifetime, glVector<float> pos, float size, glVector<float> color)
{
    m_lifetime = lifetime;
    m_position = pos;
    m_size     = size;
    m_color    = color;
    m_alive = true;
    m_birthday = 0;
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
    m_lifetime--;
    if(m_lifetime == 0)
    {
        m_alive = false;
    }
}

void PartikelExplosion::render()
{
    glVector<float> side = Game::getFighter()->getSide();
    side.normalize();
    glVector<float> up = Game::getFighter()->getUp();
    up.normalize();

    glVector<float> vec1 = m_position + side * 30;
    glVector<float> vec2 = m_position + up * 30;
    glVector<float> vec3 = m_position + side *30 + up * 30;


    glDisable ( GL_LIGHTING ) ;

    glBegin(GL_Points); //starts drawing of point
        glColor3f(m_color[0], m_color[1], m_color[2]);
        glVertex3f(m_position[0], m_position[1], m_position[2]);
    glEnd();

    glEnable ( GL_LIGHTING ) ;
}
