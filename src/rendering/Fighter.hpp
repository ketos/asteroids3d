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
     * @param printFighter decides if the fighter should be painted
     */
    void render(bool printFighter);
    /**
     * @brief calls the bullets' render method.
     */
   void renderBullet();
    /**
     * @brief returns a vetor width all bullets
     */
	vector<Bullet*> get_Bullets();
    /**
     * @brief kills a specific bullet
     */
   void killBullet(Bullet* b);

    /**
     * @brief increses the damage
     * @param i given damage
     */
    void increaseDamage(int i);
    /**
     * @brief change the speed
     */
    void changeSpeed(float change);
    /**
     * @brief change Rotationangles
     */
    void changeAngle(int axis, float change);

    /**
     * @brief returns the actual damage
     * @return actual damage
     */
    int getDamage();
    /**
     *@brief returns the actual speed
     *@return actual speed
     */
    float getSpeed();
    /**
     *@brief returns the actual score
     *@return actual score
     */
	int getScore();

	/*
     * @brief if the fighter has shot
     * @return true if the fighter shot
     */ 
	bool wasShot();

	/**
	 *@brief resets Damage
	 *
	 */
	void resetDamage();
    
	void reset_position();
    
    void reduceAngle();
    
    void setNULL();

private:
     //bool for shot
     bool shot;
    // A vector with the bullets this fighter has shot.
	vector<Bullet*> m_bullets;
    
    float m_anglepitch;
    float m_angleyaw;
    float m_angleroll;
};

#endif /* FIGHTER_HPP_ */
