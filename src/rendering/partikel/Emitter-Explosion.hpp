/**
 * @file Emitter-Explosion.hpp
 *
 * @author gruppe3
 */
#ifndef __EMITTER_EXPLOSION_H
#define __EMITTER_EXPLOSION_H

#include "rendering/partikel/Partikel-Explosion.hpp"
#include <list>

/**
 * @brief Erzeugt und verwaltet die Partikel der Explosion
 */
class EmitterExplosion
{
public:
    /**
     * @brief Konstruktor
     */
    EmitterExplosion();

    /**
     * @brief Destruktor
     */
    ~EmitterExplosion();

    /**
     * @brief Fügt ein Partikel zur Liste hinzu, solange die maximale Partikelanzahl
     *          noch nicht erreicht ist
     * 
     * @param partikel das neue Explosionspartikel
     * @return ob es hinzugefügt werden konnte oder nicht
     */
    bool add(PartikelExplosion partikel);
    
    /**
     *  @brief updatet alle aktuell vorhandenen Partikel
     */
    void update();

    /**
     * @brief erzeugt Partikel für eine Explosion
     *
     * @param a_pos Position der Explosion / des zerstörten Asteoriden
     */
    void createPartikel(glVector<float> a_pos);
    
private:
    /**
     * @brief Liste mit den Partikel
     */
    std::list<PartikelExplosion> m_partikel;
};

#endif // __EMITTER_EXPLOSION_H
