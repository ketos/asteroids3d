#include "Asteorid.hpp"
#include "logic/Game.hpp"

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
		if(speed > 0.01)
    	{
    		speed -= 0.002;
    	}
		m_position = m_position + flight_axis * speed;
        rotate(ROLL, 0.002);
		usleep(10000);
	}
	emit destroyed(getPosition().x, getPosition().y, getPosition().z );
}

void Asteorid::destroy()
{
    SoundManager::playExplosion();

    Game::getEEmit()->createPartikel(m_position);

	alive = false;
}

glVector<float> Asteorid::getPosition()
{
	return m_position;
}

void Asteorid::changeDirection(glVector<float> dir)
{
	flight_axis = dir;
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
void Asteorid::set_speed(float s)
{
	speed = s;
}
