 /**
 * Asteorid.cpp
 *
 */

#include "Asteorid.hpp"
#include <stdio.h>
#include "io/SoundManager.hpp"
#include "rendering/Explosion2.hpp"

Asteorid::Asteorid(glVector<float> start_position, glVector<float> flight_axis)
{
    alive = true;
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
		m_position = m_position + flight_axis * speed;
		usleep(10000);
	}
	emit destroyed(getPosition().x, getPosition().y, getPosition().z );
}

void Asteorid::destroy()
{
    SoundManager::playExplosion();
    //Point3<double> d = new Point3<double>(m_position.x,m_position.y,m_position.z);
    Explosion* e = new Explosion(Point3<double>(m_position.x,m_position.y,m_position.z), 100.0, 200, 20);
    e->display();
    
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
