/**
*   @file Partikel.hhp
*   @author gruppe3
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
    Partikel();

    /**
    *   @brief Desructor
    */
    ~Partikel();

    /**
    *   @brief Aktualisiert Farbe und Lebenszeit.
    */
    virtual void update();

    /**
    *   @brief Gibt zurueck, ob Partikel noch am Leben ist.
    */
    bool isAlive();

protected:
    /**
    *   @brief Zeichnet das Partikel auf dem Bildschirm.
    *   @param tex Textur die auf das Quad gelegt wird.
    */
    void render(GLuint* tex);

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
    *   @breif Geschwindigkeit
    */
    glVector<float> m_speed;

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
};

#endif //_PARTIKEL_H
