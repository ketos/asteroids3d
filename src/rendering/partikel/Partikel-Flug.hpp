/**
*   @file Partikel-Flug.hpp
*   @author gruppe3
*/

#ifndef _PARTIKEL_FLUG_H
#define _PARTIKEL_FLUG_H

#include "rendering/partikel/Partikel.hpp"

/**
*   @brief Klasse fuer die Flug-Partikel
*/
class PartikelFlug : public Partikel
{
public:
    /**
    *   @brief  Construct an new particle
    *   @param  lifetime Lebenszeit eines Partikels
    *   @param  pos Startposition des partikels
    *   @param  size Groesse des Partikels
    *   @param  color Farbe des Partikels
    */
    PartikelFlug(int lifetime, glVector<float> pos, int size, glVector<float> color);

    void update();

    void render();

private:
    /**
    *   @brief Textur fuer alle Partikel
    */
    static GLuint tex;
};

#endif //_PARTIKEL_FLUG_H
