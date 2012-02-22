/**
 * @file
 * Fighter.hpp
 */


#ifndef FIGHTER_HPP_
#define FIGHTER_HPP_

#include "TexturedMesh.hpp"
#include <GL/glu.h>	
#include <GL/glut.h>	
#include <vector>	
#include "Bullet.hpp"

/**
 * @brief   Represents a fighter that can shoot bullets.
 */
class Fighter : public TexturedMesh
{

public:
    /**
     * @brief Adds a bullet to the fighter's vector of bullets.
     */
	void shoot();
    
    /**
     * @brief Renders the fighter and calls the bullets' render method.
     */
   	void render();
    /**
     * @brief returns a vetor width all bullets
     */
	vector<Bullet*> get_Bullets();
    /**
     * @brief kills a specific bullet
     */
        void killBullet(Bullet* b);

private:
    // A vector with the bullets this fighter has shot.
	vector<Bullet*> m_bullets;

};

#endif /* FIGHTER_HPP_ */
