
#ifndef COLLISION_HPP_
#define COLLISION_HPP_

#include <QThread>
#include <vector>	
#include "view/Galaxis.hpp"
#include "rendering/Asteorid.hpp"
#include "rendering/Bullet.hpp"
#include "rendering/Fighter.hpp"


/**
 * @brief   Represents a fighter that can shoot bullets.
 */
class Collision : public QThread
{

        public:
            /**
              * @brief create the Thread 
              * @param schiff the craft to keep on
              * @param Milchstrasse the Galaxi to keep on
              */
            Collision(Fighter* schiff, Galaxis* Milchstrasse);
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
};

#endif