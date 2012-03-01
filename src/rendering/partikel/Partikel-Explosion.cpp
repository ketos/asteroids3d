#include "rendering/partikel/Partikel-Explosion.hpp"
#include <iostream>
#include "logic/Game.hpp"
#include "io/TextureManager.hpp"

//Static Texture-Member
GLuint PartikelExplosion::tex = 0;

PartikelExplosion::PartikelExplosion(glVector<float> pos, glVector<float> speed)
{
    m_lifetime  = 200;
    m_position  = pos;
    m_size      = 10;
    m_color     = glVector<float>(1,0.5,0); //Orange
    m_alive     = true;
    m_speed     = speed * 4;
    m_alpha     = 1;

    //Load texture one time
    if(!tex)
    {
        tex = TextureManager::LoadTexture("res/images/grad.tga");
    }
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
    
    //Update Alpha-Bĺending
    if(m_lifetime <= 20)
        m_alpha -= 0.05;

    //Update Color-Bĺending
    if(m_lifetime <= 185)
    {
        m_color.y += 0.09;
        m_color.z += 0.09;
    }

}

void PartikelExplosion::render()
{
    glVector<float> side = Game::getFighter()->getSide();
    side.normalize();
    glVector<float> up = Game::getFighter()->getUp();
    up.normalize();

    glVector<float> vec1 = m_position + side * m_size;
    glVector<float> vec2 = m_position + up * m_size;
    glVector<float> vec3 = m_position + side * m_size + up * m_size;
    
    glDisable ( GL_LIGHTING ) ;
                  
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,tex);

    glEnable (GL_BLEND); 
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS); //starts drawing of quad
        glColor4f(m_color[0], m_color[1], m_color[2], m_alpha);

        glTexCoord2f(1.0f,1.0f); glVertex3f(m_position[0], m_position[1], m_position[2]);
        glTexCoord2f(1.0f,0.0f); glVertex3f(vec1[0], vec1[1], vec1[2]);
        glTexCoord2f(0.0f,0.0f); glVertex3f(vec3[0], vec3[1], vec3[2]);
        glTexCoord2f(0.0f,1.0f); glVertex3f(vec2[0], vec2[1], vec2[2]);
    glEnd();

    glEnable ( GL_LIGHTING ) ;
}
