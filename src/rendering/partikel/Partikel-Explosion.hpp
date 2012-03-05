/**
*   @file Partikel-Explosion.hpp
*   @author gruppe3
*/
#ifndef _PARTIKEL_EXPLOSION_H
#define _PARTIKEL_EXPLOSION_H

#include "rendering/partikel/Partikel.hpp"

/**
*   @brief Partikel für Flug
*/
class PartikelExplosion : public Partikel
{
public:
    /**
    *   @brief  Constructs a new particle
    *   @param  pos Startposition des partikels
    *   @param  speed Geschwindigkeit des Partikels
    */
    PartikelExplosion(glVector<float> pos, glVector<float> speed);

    /**
    *   @brief Aktualisiert Farbe und Lebenszeit.
    */
    void update();

    /**
    *   @brief Zeichnet das Partikel auf dem Bildschirm.
    */
    void render();

private:
    /**
    *   @brief Textur fuer alle Partikel
    */
    static GLuint tex;
};

#endif //_PARTIKEL_FLUG_H
