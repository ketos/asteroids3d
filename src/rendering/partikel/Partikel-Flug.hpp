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
    *   @brief  Construct an new particle
    *   @param  lifetime Lebenszeit eines Partikels
    *   @param  pos Startposition des partikels
    *   @param  size Groesse des Partikels
    *   @param  color Farbe des Partikels
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
    float m_lifetime;

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
    *   @brief Farbe
    */
    glVector<float> m_color;
    
    /**
    *   @brief Textur fuer alle Partikel
    */
    static GLuint TexID1;
};

#endif //_PARTIKEL_FLUG_H
