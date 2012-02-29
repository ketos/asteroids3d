#ifndef _EMITTER_FLUG_H
#define _EMITTER_FLUG_H

#include "rendering/partikel/Partikel-Flug.hpp"
#include <list>
// http://www.codeworx.org/opengl_par1.php

//Emitter für Flug

class EmitterFlug
{
public:
    //Konstruktor
    EmitterFlug();
    EmitterFlug(int Partikelanzahl);
    //Destruktor
    ~EmitterFlug();

    //returnt aktuelle Zahl an Partikeln
    int getaktPartikelzahl();
    //neuer Partikel hinzufügen
    bool add(PartikelFlug partikel);
    // alle updaten
    void update();
    
    void createPartikel();
    
    void setMaxPartikel(int i);
    
    static float m_fFrameTime;
    static float m_fCurTime;

private:
    //alle Partikel
    std::list<PartikelFlug> m_partikel;
    //aktuelle Anzahl von Partikeln
    int m_PartikelZahl;
    //Maximale Anzahl an Partikeln
    int m_maxPartikel;
};

#endif //_EMITTER_FLUG_H
