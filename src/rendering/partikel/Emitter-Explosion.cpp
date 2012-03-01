#include "rendering/partikel/Emitter-Explosion.hpp"

#include "logic/Game.hpp"
#include "math/Global.hpp"
#include <math.h>

EmitterExplosion::EmitterExplosion()
{
        m_PartikelZahl = 0;
        m_maxPartikel = 600;
}

EmitterExplosion::~EmitterExplosion()
{
    
}

void EmitterExplosion::update()
{
    std::list<PartikelExplosion>::iterator ite = m_partikel.begin();
    //durchgehen
    while((ite) != m_partikel.end())
    {
        ite->update();
        if(!(*ite).isAlive())
        {
            ite = m_partikel.erase(ite);
        } else
        {
            
            (*ite).render();
            ++ite;
        }
    }
}

void EmitterExplosion::createPartikel(glVector<float> a_pos)
{
    glVector<float> pos = a_pos;
    glVector<float> front = Game::getFighter()->getFront();
    glVector<float> side = Game::getFighter()->getSide(); 
    glVector<float> up = Game::getFighter()->getUp(); 
    front.normalize();
    side.normalize();
    up.normalize();
    
    glVector<float> speed;
    float angle;
    float angle2;  
    int L = 30;
    //int B = 20;
    //float s = 1;
    for(angle = 0; angle < (2 * PI); angle += ( PI / L))
    {
        //for(angle2 = 0; angle2 < PI; angle2 += (PI / B))
        //{
            float x = cos(angle);
            float y = sin(angle);
           
            speed.x = x;
            speed.y = y;
            speed.z = 0;
            PartikelExplosion p(pos, speed);
            add(p);
            
            speed.x = 0;
            speed.y = 0.8*x;
            speed.z = 0.8*y;
            PartikelExplosion p1(pos, speed);
            add(p1);
            
            speed.x = 0.9*y;
            speed.y = 0;
            speed.z = 0.9*x;
            PartikelExplosion p2(pos, speed);
            add(p2);
            
                
            //speed.x = s * (/*sin(angle2) */ cos(angle));
            //speed.y = s * (/*sin(angle2) */ sin(angle));
            //speed.z = s * (sin(angle ));
            //std::cout << "winkel1: " << angle  << std::endl;
            //std::cout << "winkel2: " << angle2 << std::endl;
            //std::cout << "speed:  " << speed.x << ", " << speed.y << ", " << speed.z << std::endl;
            //PartikelExplosion p(pos, speed);
            //add(p);
            //speed.x = s * (sin(angle));
        //}   
    }
}

bool EmitterExplosion::add(PartikelExplosion partikel)
{   
        //Füge hinzu
        m_partikel.push_back(partikel);
        //gebe erstellt zurück
        return true;
}
