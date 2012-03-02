/**
 * @file Emitter-Explosion.cpp
 *
 * @author gruppe3
 */
#include "rendering/partikel/Emitter-Explosion.hpp"

#include "logic/Game.hpp"
#include "math/Global.hpp"
#include <math.h>

EmitterExplosion::EmitterExplosion()
{

}

EmitterExplosion::~EmitterExplosion()
{
    
}

void EmitterExplosion::update()
{
    // Iterator für die Liste
    std::list<PartikelExplosion>::iterator ite = m_partikel.begin();
    //durchgehen
    while((ite) != m_partikel.end())
    {
        //Partikel updaten
        ite->update();
        //Status abfragen
        if(!(*ite).isAlive())
        {
            // wenn Tod dann löschen
            ite = m_partikel.erase(ite);
        } else
        {
            // sonst rendern und weitergehen
            (*ite).render();
            ++ite;
        }
    }
}

void EmitterExplosion::createPartikel(glVector<float> a_pos)
{
    // Startposition der Partikel
    glVector<float> pos = a_pos;
    // Speed der Partikel
    glVector<float> speed;
    float angle;
    // Schrittweite
    int L = 40;
    // Einmal von 0 bis 2PI gehen (einmal im Kreis)
    // Dabei werden jeweils 5 Partikel auf unterschiedlichen Kreisen
    // mit unterschiedlicher Richtung und Geschwindigekti erzeugt
    // 3 Kreis erzeugen dabei mit den Zufallszahlen eine 
    // auseinander fliegende Kugel
    // 2 Kreis erzeugen 2 Kreis um die Kugel und bewegen sich
    // schneller vom Explosionszentrum fort
    for(angle = 0; angle < (2 * PI); angle += ( PI / L))
    {
        //Koordinaten berechnen
        float x = cos(angle);
        float y = sin(angle);

        //Speed setzen
        speed.x = 1.5 * x;
        speed.y = 1.5 * y;
        speed.z = 0.5 * y;
        
        // Partikel erzeugen und hinzufügen
        // Partikel 1 und 2 erzeugen die beiden äusseren Kreise
        PartikelExplosion p1(pos, speed);
        add(p1);    
            
        speed.z = speed.z * -1;
     
        PartikelExplosion p2(pos, speed);
        add(p2);    
        
        // Partikel 3   
        int rand2 = (rand() % 100 +1);
        float random = (float)rand2 * 0.002 + 0.8;

        int rand3 = (rand() % 100 +1);
        float random2 = (float)rand3 * 0.008 - 0.4;
           
        speed.x = random * x;
        speed.y = random * y;
        speed.z = random2;

        PartikelExplosion p3(pos, speed);
        add(p3);

        // Partikel 4
        rand2 = (rand() % 100 +1);
        random = (float)rand2 * 0.002 + 0.8;          

        rand3 = (rand() % 100 +1);
        random2 = (float)rand3 * 0.008 - 0.4;
            
        speed.x = random2;
        speed.y = random * x;
        speed.z = random * y;

        PartikelExplosion p4(pos, speed);
        add(p4);

        // Partikel 5
        rand2 = (rand() % 100 +1);
        random = (float)rand2 * 0.002 + 0.8;

        rand3 = (rand() % 100 +1);
        random2 = (float)rand3 * 0.008 - 0.4;

        speed.x = random * y;
        speed.y = random2;
        speed.z = random * x;

        PartikelExplosion p5(pos, speed);
        add(p5);
    }
}

bool EmitterExplosion::add(PartikelExplosion partikel)
{   
        // Füge Partikel zur Liste hinzu
        m_partikel.push_back(partikel);
        // gebe erstellt zurück
        return true;
}
