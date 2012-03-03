/**
*   @file Partikel.hhp
*/
#ifndef _PARTIKEL_H
#define _PARTIKEL_H

#include "math/glVector.hpp"
#include <QtOpenGL>

/**
*   @brief Diese Klasse repräsentiert ein Partikel
*/
class Partikel
{
public:
    /**
    *   @brief  Construct an new particle
    *   @param  lifetime Lebenszeit eines Partikels
    *   @param  pos Startposition des partikels
    *   @param  size Groesse des Partikels
    *   @param  color Farbe des Partikels
    */
    Partikel(int lifetime, glVector<float> pos, int size, glVector<float> color);

    /**
    *   @brief  Constructs a new particle
    *   @param  pos Startposition des partikels
    *   @param  speed Geschwindigkeit des Partikels
    */
    Partikel(glVector<float> pos, glVector<float> speed);

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
    *   @brief Farbe
    */
    glVector<float> m_color;

    /**
    *   @brief Textur fuer alle Partikel
    */
    static GLuint TexID1;
};

#endif //_PARTIKEL_H
