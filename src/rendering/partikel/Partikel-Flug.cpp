/**
*   @file Partikel-Flug.cpp
*   @author gruppe3
*/

#include "rendering/partikel/Partikel-Flug.hpp"
#include <iostream>
#include "logic/Game.hpp"
#include "io/TextureManager.hpp"

//Static Texture-Member
GLuint PartikelFlug::tex = 0;

PartikelFlug::PartikelFlug(int lifetime, glVector<float> pos, int size, glVector<float> color)
{
    //set all members
    m_lifetime  = lifetime;
    m_starttime = lifetime;
    m_position  = pos;
    m_size      = size;
    m_color     = color;
    m_alive     = true;
    m_alpha     = 0;

    //Load texture one time
    if(!tex)
    {
        tex = TextureManager::LoadTexture("res/images/debris.tga");
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
    Partikel::render(&tex);
}
