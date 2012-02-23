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
//     this->flight_axis = flight_axis * -1;
    alive = true;
    // same position as the fighter
    m_position = start_position;
    this->flight_axis = flight_axis;
    speed = 0.1;
}

bool Asteorid::isAlive()
{
	return alive;
}

void Asteorid::run()
{
    // Modify the Asteorid's position until the lifetime is over
	while(alive){
		m_position = flight_axis + m_position;
		usleep(10000);
	}
}

void Asteorid::destroy()
{
    SoundManager::playExplosion();
    /*
    float speed = 0.2;
    Explosion* e = new Explosion();
    for(int i=0; i<=(int)9*0.2;i++)
        e->explode(speed);
        
    */
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
