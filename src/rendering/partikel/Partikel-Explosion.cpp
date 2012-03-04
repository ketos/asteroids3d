/**
*   @file Partikel-Explosion.cpp
*   @author gruppe3
*/
#include "rendering/partikel/Partikel-Explosion.hpp"
#include <iostream>
#include "logic/Game.hpp"
#include "io/TextureManager.hpp"

//Static Texture-Member
GLuint PartikelExplosion::tex = 0;

PartikelExplosion::PartikelExplosion(glVector<float> pos, glVector<float> speed)
{
    //Randomize lifetime
    m_lifetime  = (rand() %30 +1) + 100; //= 200;
    //init all members
    m_starttime = m_lifetime;
    m_position  = pos;
    m_size      = 10;

    //Randomize Color
    float y = ((float)rand() / (float)RAND_MAX) - 0.5;
    m_color     = glVector<float>(1, y, 0); //Orange
    m_alive     = true;
    m_speed     = speed * 4;
    m_alpha     = 1;
}

void PartikelExplosion::update()
{
    //Update Lifetime
    --m_lifetime;
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
    if(m_lifetime <= (m_starttime - 10))
    {
        m_color.y += 0.05;
        m_color.z += 0.05;
    }

}

void PartikelExplosion::render()
{
    //Load texture one time
    if(!tex)
    {
        tex = TextureManager::LoadTexture("res/images/grad.tga");
    }
    Partikel::renderQuad(&tex);
}
