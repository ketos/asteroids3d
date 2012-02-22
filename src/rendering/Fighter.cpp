/**
 * Fighter.cpp
 *
 */


#include "Fighter.hpp"
#include <stdio.h>
#include "rendering/TexturedMesh.hpp"
#include "rendering/Fighter.hpp"
#include "io/Read3DS.hpp"
void Fighter::shoot()
{
    
    // Create a new bullet with this fighter's position an x-Axis
	Bullet* b = new Bullet(m_position, m_xAxis);
	Read3DS reader("arrow.3ds");
	reader.getMesh(*(static_cast<TexturedMesh*>(b)));
    // Start a new thread, move the bullet
	b->start();
    // Add it to this fighter's vector of bullets
	m_bullets.push_back(b);
}

vector<Bullet*> Fighter::get_Bullets()
{
 return m_bullets; 
}

void Fighter::render()
{
    // Render the fighter
    TexturedMesh::render();
    vector<Bullet*>::iterator bulletIt;
    bulletIt = m_bullets.begin();
    // Iterate over the fighter's bullets and render them
    // if the bullet's lifetime is over, erase it from the vector.
    while(bulletIt != m_bullets.end()){
        (*bulletIt)->render();
        if(!(*bulletIt)->isAlive()){
            bulletIt = m_bullets.erase(bulletIt);
	    }else{
	        bulletIt++;	
	    }
    }
}
