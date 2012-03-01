#include "rendering/partikel/Emitter-Explosion.hpp"

#include "logic/Game.hpp"
#include "math/Global.hpp"

EmitterExplosion::EmitterExplosion()
{
    m_maxPartikel = 400;
    m_PartikelZahl = 0;
}

EmitterExplosion::EmitterExplosion(int Partikelanzahl)
{
    m_maxPartikel = Partikelanzahl;
    m_PartikelZahl = 0;
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
    int L = 4;
    int B = 4;
    for(angle = 0; angle < (2 *PI); angle += (2 * PI / L))
    {
        for(angle2 = 0; angle2 < PI; angle2 += (PI / B))
        {
            speed.x = (sin(angle2 * PW) * cos(angle * PW));
            speed.y = (sin(angle2 * PW) * sin(angle * PW));
            speed.z = (sin(angle  * PW));
            PartikelExplosion p(pos, speed);
            add(p);
        }   
    }    
                
    PartikelExplosion p1(pos, front);
    add(p1);
    PartikelExplosion p2(pos, -front);
    add(p2);
    PartikelExplosion p3(pos, up);
    add(p3);
    PartikelExplosion p4(pos, -up);
    add(p4);
    PartikelExplosion p5(pos, side);
    add(p5);
    PartikelExplosion p6(pos, -side);
    add(p6);
}

bool EmitterExplosion::add(PartikelExplosion partikel)
{   
    //wenn noch Platz
    if(m_partikel.size() < m_maxPartikel)
    {   
        //Füge hinzu
        m_partikel.push_back(partikel);
        //gebe erstellt zurück
        return true;
    }
    //gebe nicht erstellt zurück
    return false;
}
