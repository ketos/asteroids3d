#include "rendering/partikel/Partikel-Flug.hpp"
#include <iostream>
#include "logic/Game.hpp"
#include "io/TextureManager.hpp"

//Static Texture-Member
GLuint PartikelFlug::TexID1 = 0;

PartikelFlug::PartikelFlug(float lifetime, glVector<float> pos, int size, glVector<float> color)
{
    //set all members
    m_lifetime  = lifetime;
    m_position  = pos;
    m_size      = size;
    m_color     = color;
    m_alive     = true;
    m_alpha     = 0;

    //Load texture one time
    if(!TexID1)
    {
        TexID1 = TextureManager::LoadTexture("res/images/debris.tga");
    }
}

PartikelFlug::~PartikelFlug()
{
    //nothing to do
}

bool PartikelFlug::isAlive()
{
    //give alive status
    return m_alive;
}

void PartikelFlug::update()
{
    //Update lifetime
    m_lifetime--;
    if(m_lifetime == 0)
    {
        m_alive = false;
        return;
    }

    //Update Alpha-Bĺending
    if(m_lifetime >= (m_lifetime-10))
    {
        m_alpha += 0.1;
    }
    else if(m_lifetime <= 10)
    {
        m_alpha -= 0.1;
    }
}

void PartikelFlug::render()
{
    //calcualte heading
    glVector<float> side = Game::getFighter()->getSide();
    side.normalize();
    glVector<float> up = Game::getFighter()->getUp();
    up.normalize();

    glVector<float> vec1 = m_position + side * m_size;
    glVector<float> vec2 = m_position + up * m_size;
    glVector<float> vec3 = m_position + side * m_size + up * m_size;

    //render particle quad with texture
    glDisable ( GL_LIGHTING ) ;
                  
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,TexID1);

    //use alpha channel
    glEnable (GL_BLEND); 
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS); //starts drawing of quad
        glColor4f(1.0f,1.0f,1.0f, m_alpha);
        //draw quad with this four points
        glTexCoord2f(1.0f,1.0f); glVertex3f(m_position[0], m_position[1], m_position[2]);
        glTexCoord2f(1.0f,0.0f); glVertex3f(vec1[0], vec1[1], vec1[2]);
        glTexCoord2f(0.0f,0.0f); glVertex3f(vec3[0], vec3[1], vec3[2]);
        glTexCoord2f(0.0f,1.0f); glVertex3f(vec2[0], vec2[1], vec2[2]);
    glEnd();

    glEnable ( GL_LIGHTING ) ;
}
