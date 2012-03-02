/**
*   @file Partikel-Flug.hpp
*   @author gruppe3   
*/

#ifndef _PARTIKEL_FLUG_H
#define _PARTIKEL_FLUG_H

#include "math/glVector.hpp"
#include <QtOpenGL>

/**
*   @brief Klasse fuer die Flug-Partikel
*/
class PartikelFlug
{
public:
    /**
    *   @brief
    *   @param  float Lebenszeit eines Partikels
    *   @param  glvector<float> Startposition des partikels
    *   @param  int Groesse des Partikels
    *   @param  glVector<float> Farbe des Partikels
    */
    PartikelFlug(float lifetime, glVector<float> pos, int size, glVector<float> color);
    
    /**
    *   @brief Desructor
    */
    ~PartikelFlug();

    /**
    *   @brief Aktualisiert Farbe und Lebenszeit.
    */
    void update();
    
    /**
    *   @breif Gibt zurueck, ob Partikel noch am Leben ist.
    */
    bool isAlive();

    /**
    *   @breif Zeichnet das Partikel auf dem Bildschirm.
    */
    void render();
private:
    /**
    *   @breif Gesundheitstatus
    */
    bool m_alive;

    /**
    *   @breif Lebensdauer
    */
    float m_lifetime;

    /**
    *   @breif Startzeit
    */
    float m_birthday;

    /**
    *   @breif aktuelle Position
    */
    glVector<float> m_position;

    /**
    *   @breif grösse
    */
    float m_size;

    /**
    *   @breif Sichtbarkeit
    */
    float m_alpha;

    /**
    *   @breif Farbe
    */
    glVector<float> m_color;
    
    /**
    *   @breif Textur fuer alle Partikel
    */
    static GLuint TexID1;
};

#endif //_PARTIKEL_FLUG_H
