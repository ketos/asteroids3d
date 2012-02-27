 /**
 * Mini_Asteorid.cpp
 *
 */

#include "Mini_Asteorid.hpp"
#include <stdio.h>
#include "io/SoundManager.hpp"

Mini_Asteorid::Mini_Asteorid(glVector<float> start_position, glVector<float> flight_axis)
:     Asteorid(start_position, flight_axis)
{
	radius = 100;
}

void Mini_Asteorid::run()
{
    // Modify the Asteorid's position until the lifetime is over
	while(alive){
		m_position = m_position + flight_axis * speed;
		usleep(10000);
	}
	emit hit();
}

