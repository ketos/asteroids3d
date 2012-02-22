 /**
 * Asteorid.cpp
 *
 */

#include "Asteorid.hpp"

Asteorid::Asteorid(glVector<float> start_position, glVector<float> flight_axis)
{
    // the Asteorid will move on this axis, it has to be reversed for the direction to be right    
    this->flight_axis = flight_axis * -1;
    alive = true;
    // same position as the fighter
    m_position = start_position;
}

bool Asteorid::isAlive()
{
	return alive;
}

void Asteorid::run()
{
    // Modify the Asteorid's position until the lifetime is over
	while(alive){
		m_position = flight_axis  + m_position;
		usleep(1000);
	}
}

void Asteorid::destroy()
{
	alive = false;
}



