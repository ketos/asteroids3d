/**
 * @file Emitter-Flug.cpp
 *
 * @author gruppe3
 */
#include "rendering/partikel/Emitter-Flug.hpp"

#include <iostream>
#include "logic/Game.hpp"
#include <stdlib.h>
#include <time.h>

EmitterFlug::EmitterFlug()
{

}

EmitterFlug::EmitterFlug(int Partikelanzahl)
{
    m_maxPartikel  = Partikelanzahl;
}

EmitterFlug::~EmitterFlug()
{

}

void EmitterFlug::setMaxPartikel(int i)
{
    m_maxPartikel = i;
}

void EmitterFlug::update()
{
    //Iterator
    std::list<PartikelFlug>::iterator ite = m_partikel.begin();
    //Liste durchgehen
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
            ++ite;
        }
    }
}

void EmitterFlug::createPartikel()
{
    //Position und Ausrichtung des Fliegers holen
    glVector<float> pos = Game::getFighter()->getPosition();
    glVector<float> front = Game::getFighter()->getFront();
    glVector<float> side = Game::getFighter()->getSide();
    glVector<float> up = Game::getFighter()->getUp();

    //Koordinatenvektoren normalisieren
    front.normalize();
    side.normalize();
    up.normalize();

    // Grösse für die Breite und Höhe des Emitterrechteck
    int max = 0;

    // verschiedene Grössen bei den unterschiedlichen Perspektiven
    if(Game::getView() == 0)
    {
        max = 2500;
    }
    else if(Game::getView() == 1)
    {
        max = 3000;
    }
    else if(Game::getView() == 2)
    {
        max = 4500;
    }

    // Entfernung des Emitterrechtecks vor dem Schiff
    int range = 2000;

    // Berechnet die Position des Partikels innerhalb des Rechtecks
    // mit Zufallswerten
    pos = pos - front * range;
    pos = pos + side * ((rand() % max) - (max/2))   + (up * ((rand() % max) - (max/2))) ;

    // Farbe
    glVector<float> color(1,1,1); //White

    // Erstellen und hinzufügen des Partikels
    PartikelFlug p(50, pos, 20, color);
    add(p);
}

bool EmitterFlug::add(PartikelFlug partikel)
{
    // Wenn die Maximalzahl noch nicht erreicht
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
