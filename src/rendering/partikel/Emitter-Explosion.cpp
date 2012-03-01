#include "rendering/partikel/Emitter-Explosion.hpp"

#include "logic/Game.hpp"

EmitterExplosion::EmitterExplosion()
{
        m_PartikelZahl = 0;
        m_maxPartikel = 6;
}

EmitterExplosion::~EmitterExplosion()
{
    
}

void EmitterExplosion::update()
{
    std::cout << "update mich" << std::endl;
    std::list<PartikelExplosion>::iterator ite = m_partikel.begin();
    //durchgehen
    while((ite) != m_partikel.end())
    {
        std::cout << "render mich" << std::endl;
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
    
    PartikelExplosion p1(pos, front);
    add(p1);
    PartikelExplosion p2(pos, front*(-1));
    add(p2);
    PartikelExplosion p3(pos, up);
    add(p3);
    PartikelExplosion p4(pos, up*(-1));
    add(p4);
    PartikelExplosion p5(pos, side);
    add(p5);
    PartikelExplosion p6(pos, side*(-1));
    add(p6);
}

bool EmitterExplosion::add(PartikelExplosion partikel)
{   
        //Füge hinzu
        m_partikel.push_back(partikel);
        //gebe erstellt zurück
        return true;
}
