/**
*   @file Partikel-Flug.cpp
*   @author gruppe3
*/

#include "rendering/partikel/Partikel-Flug.hpp"
#include <iostream>
#include "logic/Game.hpp"
#include "io/TextureManager.hpp"

//Static Texture-Member
GLuint PartikelFlug::tex[3] = {0,0,0};
int sizes[3] = {20,18,22};

PartikelFlug::PartikelFlug(int lifetime, glVector<float> pos, glVector<float> color)
{
    //set all members
    m_lifetime  = lifetime;
    m_starttime = lifetime;
    m_position  = pos;
    m_color     = color;
    m_alive     = true;
    m_alpha     = 0;
    m_index     = (int)rand() % 3;
    m_size      = sizes[m_index];

    //Load texture one time
    if(!tex[0])
    {
        tex[0] = TextureManager::LoadTexture("res/images/debris.tga");
        tex[1] = TextureManager::LoadTexture("res/images/debris2.tga");
        tex[2] = TextureManager::LoadTexture("res/images/debris3.tga");
    }

}

void PartikelFlug::update()
{
    //Update lifetime
    --m_lifetime;
    if(m_lifetime == 0)
    {
        m_alive = false;
        return;
    }

    //Update Alpha-Bĺending
    if(m_lifetime >= (m_starttime - 10))
    {
        m_alpha += 0.1;
    }

    if(m_lifetime <= 10)
    {
        m_alpha -= 0.1;
    }
}

void PartikelFlug::render()
{
    Partikel::renderQuad(&tex[m_index]);
}
