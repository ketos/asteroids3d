#include "rendering/partikel/Emitter-Flug.hpp"
// http://www.codeworx.org/opengl_par1.php

#include <iostream>
#include "logic/Game.hpp"
//Emitter für Flug

EmitterFlug::EmitterFlug()
{

}

EmitterFlug::EmitterFlug(int Partikelanzahl)
{
    m_maxPartikel  = Partikelanzahl;
    m_PartikelZahl = 0;
}

EmitterFlug::~EmitterFlug()
{
    //TODO alle Partikel löschen
}

void EmitterFlug::setMaxPartikel(int i)
{
    m_maxPartikel = i;
    m_PartikelZahl =0;
}

void EmitterFlug::update()
{   
    std::list<PartikelFlug>::iterator ite = m_partikel.begin();
    //durchgehen
    while((ite) != m_partikel.end())
    {   
        //updaten
        ite->update();
        //alive abfragen
        if(!(*ite).isAlive()) //wenn nicht mehr am Leben
        {   
            ite = m_partikel.erase(ite);
        } else
        {   
            //wenn alive rendern;
            (*ite).render();
            ite++;
        }
    }
}

void EmitterFlug::createPartikel()
{   
    glVector<float> pos;
    glVector<float> front = Game::getFighter()->getFront();
    front.normalize();
    pos = Game::getFighter()->getPosition() + front * 1000;
    float size = 20;
    glVector<float> color(0,0,0);
 //   PartikelFlug p(400, pos, size, color);
 //   add(p);

    PartikelFlug p(400, pos, size, color);
    //Read 3ds for Rocket
    Read3DS reader("res/models/particle.3ds");
    reader.getMesh(*(static_cast<TexturedMesh*>(&p)));
    add(p);
}

bool EmitterFlug::add(PartikelFlug partikel)
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
