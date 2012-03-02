/**
*   @file Partikel-Explosion.hpp
*   @author gruppe3
*/
#ifndef _PARTIKEL_EXPLOSION_H
#define _PARTIKEL_EXPLOSION_H

#include "math/glVector.hpp"
#include <QtOpenGL>

/**
*   @breif Partikel für Flug
*/
class PartikelExplosion
{
public:
    /**
    *   @brief  Constructs a new particle
    *   @param  glvector<float> Startposition des partikels
    *   @param  glVector<float> Geschwindigkeit des Partikels
    */
    PartikelExplosion(glVector<float> pos, glVector<float> speed);
    
    /**
    *   @brief Desructor
    */
    ~PartikelExplosion();

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
    float m_startlife;

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
    *   @breif Geschwindigkeit
    */
    glVector<float> m_speed;
       
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
