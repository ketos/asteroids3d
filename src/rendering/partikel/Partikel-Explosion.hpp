/**
*   @file Partikel-Explosion.hpp
*   @author gruppe3
*/
#ifndef _PARTIKEL_EXPLOSION_H
#define _PARTIKEL_EXPLOSION_H

#include "math/glVector.hpp"
#include <QtOpenGL>

/**
*   @brief Partikel für Flug
*/
class PartikelExplosion
{
public:
    /**
    *   @brief  Constructs a new particle
    *   @param  pos Startposition des partikels
    *   @param  speed Geschwindigkeit des Partikels
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
    *   @brief Gibt zurueck, ob Partikel noch am Leben ist.
    */
    bool isAlive();

    /**
    *   @brief Zeichnet das Partikel auf dem Bildschirm.
    */
    void render();
private:
    /**
    *   @brief Gesundheitstatus
    */
    bool m_alive;

    /**
    *   @brief Lebensdauer
    */
    int m_lifetime;

    /**
    *   @brief Start-Lebensdauer
    */
    int m_starttime;

     /**
    *   @brief aktuelle Position
    */
    glVector<float> m_position;

    /**
    *   @brief grösse
    */
    float m_size;

    /**
    *   @brief Sichtbarkeit
    */
    float m_alpha;

    /**
    *   @brief Geschwindigkeit
    */
    glVector<float> m_speed;
       
    /**
    *   @brief Farbe
    */
    glVector<float> m_color;
    
    /**
    *   @brief Textur fuer alle Partikel
    */
    static GLuint TexID2;
};

#endif //_PARTIKEL_FLUG_H
