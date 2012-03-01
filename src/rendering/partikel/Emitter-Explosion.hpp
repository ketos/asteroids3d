#ifndef __EMITTER_EXPLOSION_H
#define __EMITTER_EXPLOSION_H

#include "rendering/partikel/Partikel-Explosion.hpp"
#include <list>

class EmitterExplosion
{
public:
    EmitterExplosion();
    EmitterExplosion(int Partikelanzahl);
    ~EmitterExplosion();

    int getaktPartikel();
    bool add(PartikelExplosion partikel);
    void update();

    createPartikel();
    void setMaxPartikel();
    
private:
    std::list<PartikelExplosion> m_partikel;
    int m_PartikelZahl;
    unsigned int m_maxPartikel;
};

#endif // __EMITTER_EXPLOSION_H
