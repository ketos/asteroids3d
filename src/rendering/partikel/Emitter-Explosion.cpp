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
    //float angle2;  
    int L = 10;
    //int B = 20;
    //float s = 1;
    for(angle = 0; angle < (2 * PI); angle += ( PI / L))
    {
        //for(angle2 = 0; angle2 < PI; angle2 += (PI / B))
        //{
            float x = cos(angle);
            float y = sin(angle);
    
            int rand3 = (rand() % 100 +1);
            float random2 = (float)rand3 * 0.001 - 0.05;

            speed.x = 1.5 * x;
            speed.y = 1.5 * y;
            speed.z = 0.5 * y;//random2;
            
            PartikelExplosion p0(pos, speed);
            add(p0);    
            
            speed.z = speed.z * -1;

            
            PartikelExplosion p4(pos, speed);
            add(p4);    
            
            int rand2 = (rand() % 100 +1);
            float random = (float)rand2 * 0.002 + 0.8;

            rand3 = (rand() % 100 +1);
            random2 = (float)rand3 * 0.008 - 0.4;
           
            speed.x = random * x;
            speed.y = random * y;
            speed.z = random2;
            PartikelExplosion p(pos, speed);
            add(p);

            rand2 = (rand() % 100 +1);
            random = (float)rand2 * 0.002 + 0.8;          

            rand3 = (rand() % 100 +1);
            random2 = (float)rand3 * 0.008 - 0.4;
            
            speed.x = random2;
            speed.y = random * x;
            speed.z = random * y;
            PartikelExplosion p1(pos, speed);
            add(p1);

            rand2 = (rand() % 100 +1);
            random = (float)rand2 * 0.002 + 0.8;

            rand3 = (rand() % 100 +1);
            random2 = (float)rand3 * 0.008 - 0.4;

            speed.x = random * y;
            speed.y = random2;
            speed.z = random * x;
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
