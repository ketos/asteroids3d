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
	mini = true;
	hitable = true;
	speed = 0.2;
}

void Mini_Asteorid::run()
{
	
    // Modify the Asteorid's position until the lifetime is over
	while(alive){
	    if(speed > 0.01)
    	{
    		speed -= 0.002;
    	}
		m_position = m_position + flight_axis * speed;
		usleep(10000);
	}
	emit hit();
}

