
#ifndef COLLISION_HPP_
#define COLLISION_HPP_

#include <QThread>
#include <vector>	
#include "view/Galaxis.hpp"
#include "rendering/Asteorid.hpp"
#include "rendering/Bullet.hpp"
#include "rendering/Fighter.hpp"
#include  "math/glVector.hpp"
#include <vector>
#include <math.h>
#include <iostream>


/**
 * @brief   Represents a fighter that can shoot bullets.
 */
class Collision : public QThread
{

        public:
            Collision(Fighter* schiff, Galaxis* Milchstrasse);

            /**
             * @brief Moves the bullet until it's lifetime is over.
             */
            void run();
            /**
             * @brief stops the thread
             */
            void stop();
	    /**
	     * @brief returns the vector containing the nearest astroids
             * @return vector containing the nearest astroids
	     */
	    vector<glVector<float>*> getCollisionVector();

        private:
            //fighter
                Fighter* m_craft;
            //Galaxis
                Galaxis* m_galax;
            //bullets
                vector<Bullet*> m_bullets;
            //asteorids
                vector<Asteorid*> m_asteorids;
            // if the collision algo is alive
                bool m_running;
            //Vector for radar
	        vector<glVector<float>*> radar;
};

#endif
