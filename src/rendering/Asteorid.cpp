 /**
 * Asteorid.cpp
 *
 */

#include "Asteorid.hpp"
#include <stdio.h>
#include "io/SoundManager.hpp"
//#include "rendering/Explosion.hpp"

Asteorid::Asteorid(glVector<float> start_position, glVector<float> flight_axis)
{
    alive = true;
    m_position = start_position;
    this->flight_axis = flight_axis;
    speed = 0.02;
    radius = 350;
    mini = false;
    hitable = true;
    wait = 0;
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
	std::cout << "Ich emmitire das destroyed signal, bzw. der Thread ist tot" << std::endl;
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
	std::cout << "Der Asteorid ist zusammengeprallt und soll irgendwas tun";
    flight_axis = flight_axis * -2;
}

glVector<float> Asteorid::getFlightAxis()
{
    return flight_axis;
}

void Asteorid::set_flight_axis(glVector<float> new_axis)
{
	flight_axis = new_axis;
}

float Asteorid::get_radius()
{
	return radius;
}

bool Asteorid::is_mini()
{
	return mini;
}

bool Asteorid::is_hitable()
{
	return hitable;
}

void Asteorid::set_hitable(bool hit)
{
	hitable = hit;
}
