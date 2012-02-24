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
    // the Asteorid will move on this axis, it has to be reversed for the direction to be right    
    //alive = true;
    // same position as the fighter
    //m_position = start_position;
    //this->flight_axis = flight_axis;
    //speed = 0.1;
}

void Mini_Asteorid::info()
{
    std::cout << "Dies das info" << std::endl;
}
