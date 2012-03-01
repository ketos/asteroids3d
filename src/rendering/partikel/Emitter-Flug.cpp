#include "rendering/partikel/Emitter-Flug.hpp"
// http://www.codeworx.org/opengl_par1.php

#include <iostream>
#include "logic/Game.hpp"
#include <stdlib.h>
#include <time.h>
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
            ++ite;
        }
    }
}

void EmitterFlug::createPartikel()
{   
    glVector<float> pos;
    glVector<float> front = Game::getFighter()->getFront();
    glVector<float> side = Game::getFighter()->getSide(); 
    glVector<float> up = Game::getFighter()->getUp(); 
    front.normalize();
    side.normalize();
    up.normalize();
    int max = 0;
    if(Game::getView() == 0)
    {
        max = 2000;
    }
    else if(Game::getView() == 1)
    {
        max = 2500;
    } 
    else if(Game::getView() == 2)
    {
        max = 4000;
    }
    int range = 2000;
    pos = Game::getFighter()->getPosition() - front * range;
    pos = pos + side * ((rand() % max) - (max/2))   + (up * ((rand() % max) - (max/2))) ;
    float size = 20;
    glVector<float> color(0,0,0);
    PartikelFlug p(50, pos, size, color);
    add(p);
    //std::cout << "p: " << pos[0] << "," << pos[1] << "," << pos[2] << std::endl;
}

bool EmitterFlug::add(PartikelFlug partikel)
{
