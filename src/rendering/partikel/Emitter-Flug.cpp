#include "rendering/partikel/Emitter-Flug.hpp"
// http://www.codeworx.org/opengl_par1.php

//Emitter für Flug

EmitterFlug::EmitterFlug(int Partikelanzahl)
{
    m_maxPartikel  = Partikelanzahl;
    m_PartikelZahl = 0;
}

EmitterFlug::~EmitterFlug()
{
    //TODO alle Partikel löschen
}

void EmitterFlug::update()
{   
    std::list<PartikelFlug*>::iterator ite = m_partikel.begin();
    //durchgehen
    while(ite != m_partikel.end())
    {   
        //updaten
        (*ite)->update();
        //alive abfragen
        if(!(*ite)->isAlive()) //wenn nicht mehr am Leben
        {   
            m_partikel.erase(ite);
            delete (*ite);
        } else
        {   
            //wenn alive rendern;
            (*ite)->render();
        }
        //weitergehen;
        ite++;
    }
}

bool EmitterFlug::add(PartikelFlug* partikel)
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
