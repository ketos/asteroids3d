#ifndef _PARTIKEL_FLUG_H
#define _PARTIKEL_FLUG_H

#include "math/glVector.hpp"
// Partikel für Flug

class PartikelFlug
{
public:
    //Konstruktor
    PartikelFlug(float lifetime, glVector<float> pos, float size, glVector<float> color);
    //Destruktor
    ~PartikelFlug();
    // weitersetzen
    void update();
    //rendern
    void render();
    
    bool isAlive();
private:
    //Gesundheitstatus
    bool m_alive;
    //Lebensdauer
    float m_lifetime;
    //Startzeit
    float m_birthday;
    //aktuelle Position
    glVector<float> m_position;
    //grösse
    float m_size;
    //Farbe
    glVector<float> m_color;  
};

#endif //_PARTIKEL_FLUG_H