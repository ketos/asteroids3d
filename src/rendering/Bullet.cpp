 /**
 * Bullet.cpp
 *
 */

#include "Bullet.hpp"

Bullet::Bullet(glVector<float> fighter_position, glVector<float> fighter_axis)
{
    // the Bullet will move on this axis, it has to be reversed for the direction to be right    
    this->fighter_axis = fighter_axis * -1;
    alive = true;
    // same position as the fighter
    m_position = fighter_position;
}

bool Bullet::isAlive()
{
	return alive;
}

void Bullet::run()
{
	int i = 0;
    // Modify the Asteorid's position until the lifetime is over
	while(i < lifetime){
		m_position = fighter_axis  + m_position;
		i++;
		usleep(1000);
	}
	alive = false;
}



