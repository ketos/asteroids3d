 /**
 * Asteorid.cpp
 *
 */

#include "Asteorid.hpp"
#include <stdio.h>
#include "io/SoundManager.hpp"
#include "rendering/Explosion.hpp"

Asteorid::Asteorid(glVector<float> start_position, glVector<float> flight_axis)
{
    // the Asteorid will move on this axis, it has to be reversed for the direction to be right    
    alive = true;
    // same position as the fighter
    m_position = start_position;
    this->flight_axis = flight_axis;
    speed = 0.01;
}

bool Asteorid::isAlive()
{
	return alive;	
}

void Asteorid::run()
{
    // Modify the Asteorid's position until the lifetime is over
	while(alive){
		m_position = m_position + flight_axis *speed;
		usleep(10000);
	}
	emit destroyed(getPosition().x, getPosition().y, getPosition().z );
}

void Asteorid::destroy()
{
    SoundManager::playExplosion();
    //Explosion* e = new Explosion();
    //e->Explode();
    
	alive = false;
	
}

glVector<float> Asteorid::getPosition()
{
        return m_position;
}

void Asteorid::changeDirection()
{
    flight_axis = flight_axis * -1;
}

glVector<float> Asteorid::getFlightAxis()
{
    return flight_axis;
}
