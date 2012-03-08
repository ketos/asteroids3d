 /**
 * Bullet.cpp
 *
 */

#include "Bullet.hpp"

// static speed of all bullets
float Bullet::b_speed = 3;

Bullet::Bullet(glVector<float> fighter_position, glVector<float> fighter_axis, glVector<float> asteroid)
{
   	target = asteroid;
	this->fighter_axis = (fighter_position - target)* - (b_speed);
	alive = true;
        // same position as the fighter
 	m_position = fighter_position;
 	//play sound
        SoundManager::playFireSound();
        seeking = true;
}

Bullet::Bullet(glVector<float> fighter_position, glVector<float> fighter_axis)
{
    // the Bullet will move on this axis, it has to be reversed for the direction to be right
    fighter_axis.normalize();  
    this->fighter_axis = fighter_axis * - b_speed;
    alive = true;
    // same position as the fighter
    m_position = fighter_position;
    SoundManager::playFireSound();
    seeking=false;
}

bool Bullet::isAlive()
{
	return alive;
}

void Bullet::run()
{
        // Modify the Asteorid's position until the lifetime is over
        int i = 0;
	while( (i < lifetime) && (alive) )
	{
		m_position = fighter_axis  + m_position;
		usleep(1000);
	        i++;
	}
	alive = false;
}
void Bullet::kill()
{
        alive = false;
}

glVector<float> Bullet::getPosition()
{
        return m_position;
}
void Bullet::setAxis(glVector<float> xA, glVector<float> yA, glVector<float> zA)
{
        // set axis
        m_xAxis = xA;
        m_yAxis = yA;
        m_zAxis = zA;
}





