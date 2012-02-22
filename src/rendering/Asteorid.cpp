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
		std::cout << "flight axis x" << flight_axis.x << std::endl;
		std::cout << "flight axis y" << flight_axis.y << std::endl;
		std::cout << "flight axis z" << flight_axis.z << std::endl;
		std::cout << "m_position x" << m_position.x << std::endl;
		std::cout << "m_position y" << m_position.y << std::endl;
		std::cout << "m_position z" << m_position.z << std::endl;

// 		std::cout << 	"Der Asteorid soll sich bewegen: " << m_position.x << std::endl;
		usleep(1000000);
	}
}

void Asteorid::destroy()
{
	alive = false;
}



