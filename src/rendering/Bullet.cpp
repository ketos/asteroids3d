/**
 * Bullet.cpp
 *
 */

#include "Bullet.hpp"
#include <iostream>
#include <QGLBuilder>

using namespace std;

Bullet::Bullet(glVector<float> fighter_position, glVector<float> fighter_axis)
{
    // the bullet will move on this axis, it has to be reversed for the direction to be right    
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
	//cout << "thread lauft..."<< endl;
	int i = 0;
        // Modify the bullet's position until the lifetime is over
	while(i < lifetime){
		m_position = fighter_axis  + m_position;
		i++;
		render();
		usleep(1000);
	}
	alive = false;
	cout << "bullet tot..."<<endl;
}

void Bullet::render()
{
	  cout << "rendern..."<<endl;
	  QGLBuilder builder;
 builder << QGLSphere(2);
 QGLSceneNode *node = builder.finalizedSceneNode();

 painter.translate(10, 25, 0);
 node->draw(&painter);
	 
}



