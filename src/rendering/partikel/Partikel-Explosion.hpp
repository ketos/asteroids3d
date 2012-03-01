#ifndef _PARTIKEL_EXPLOSION_H
#define _PARTIKEL_EXPLOSION_H

#include "math/glVector.hpp"

// Partikel für Flug

class PartikelExplosion
{
public:
    //Konstruktor
    PartikelExplosion(float lifetime, glVector<float> pos, float size, glVector<float> color);
    //Desructor
    ~PartikelExplosion();
    // weitersetzen
    void update();
    
    bool isAlive();

    void render();
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

    glVector<float> m_speed;
       
    static GLuint TexID1;
};

#endif //_PARTIKEL_FLUG_H
