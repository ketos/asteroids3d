 /**
 * Asteorid.cpp
 *
 */

#include "Asteorid.hpp"
#include <stdio.h>

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
// 		std::cout << "Der Asteorid soll sich bewegen: " << m_position.x << std::endl;
		m_position = flight_axis  + m_position;

// 		std::cout << 	"Der Asteorid soll sich bewegen: " << m_position.x << std::endl;
		usleep(10000);
	}
}

void Asteorid::destroy()
{
	alive = false;
}

glVector<float> Asteorid::getPosition()
{
        return m_position;
}
