/**
 *  @file Galaxis.hpp
 *  @author gruppe3
 */
#ifndef COLLISION_HPP_
#define COLLISION_HPP_

#include <QThread>
#include <QMutex>
#include <vector>	
#include "rendering/Asteorid.hpp"
#include "rendering/Bullet.hpp"
#include "math/glVector.hpp"
#include <vector>
#include <math.h>
#include <iostream>



/**
 * @brief   Represents a fighter that can shoot bullets.
 */
class Collision : public QThread
{

public:
  	/**
   	 * @brief create the Thread 
   	 */
	Collision();
	
  	/**
   	 * @brief Deletes the Collision Thread
   	 */
   	virtual ~Collision() {};
   
  	/**
     * @brief Moves the bullet until it's lifetime is over.
   	 */
   	void run();
   
  	/**
   	 * @brief return if thred is running
   	 * @return if thread is running
   	 */
   	bool isRunning();
            
  	/**
   	 * @brief stops the thread
   	 */
   	void stop();
   
  	/**
	 * @brief returns the vector containing the nearest astroids
   	 * @return vector containing the nearest astroids
	 */
	vector<glVector<float>*> getCollisionVector();
	    
  	/**
	 * @brief return true if a Astroid is closer than 300
	 */
   bool getWarning();
   
private:
  	/**
	 * @brief Vector of Bullets
	 */
   	vector<Bullet*> m_bullets;
  	/**
	 * @brief Vector of Asteorids
	 */
   	vector<Asteorid*> m_asteorids;
  	/**
	 * @brief Boolean if the Collision Algo is running
	 */
   	bool m_running;
  	/**
	 * @brief Vector for Bullets
	 */
	vector<glVector<float>*> radar;
  	/**
	 * @brief Vector for Bullets
	 */
	vector<glVector<float>*> radar2;
  	/**
	 * @brief Warning Boolean
	 */
   bool warning;
  	/**
	 * @brief Mutex
	 */
   QMutex mutex;
            
};

#endif
