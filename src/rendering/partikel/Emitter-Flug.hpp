/**
 * @file Emitter-Flug.hpp
 *
 * @author gruppe3
 */

#ifndef _EMITTER_FLUG_H
#define _EMITTER_FLUG_H

#include "rendering/partikel/Partikel-Flug.hpp"
#include <list>

/**
 * @brief Emitter für die Flugklasse
 *        Verwaltet die Partikel die während des Fluges entstehen
 *        damit ein Gefühl für die Geschwindigkeit entsteht
 */

class EmitterFlug
{
public:
    /**
     * @brief Konstruktor
     */
    EmitterFlug();
    /**
     * @brief Konstruktor
     *
     * @param Partikelanzahl Die Maximale Anzahl an Partikeln
     */
    EmitterFlug(int Partikelanzahl);
    
    /**
     * @brief Destruktor
     */
    ~EmitterFlug();

    /**
     * @brief Fügt ein Partikel zur Liste hinzu, 
     *        solange die Maximale anzahl noch nicht erreicht ist
     *
     * @param partikel  Partikel
     * @return wurde hinzugefügt oder nicht
     */
    bool add(PartikelFlug partikel);
    
    /**
     * @brief Partikel werden geupdatet, gerendet oder gelöscht
     */
    void update();
    
    /**
     * @brief erzeugt ein neues Partikel
     */
    void createPartikel();
    
    /**
     * @brief Ändern der Maximalen Partikelanzahl
     * 
     * @param i Anzahl
     */
    void setMaxPartikel(int i);

private:
    /**
     * @brief Liste mit allen Partikeln
     */
    std::list<PartikelFlug> m_partikel;
    
    /**
     * @brief Maximala Anzahl an Partikeln
     */
    unsigned int m_maxPartikel;
};

#endif //_EMITTER_FLUG_H
