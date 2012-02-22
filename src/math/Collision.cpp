#include "Collision.hpp"
#include <iostream>

using namespace std;

Collision::Collision(Fighter* schiff, Galaxis* Milchstrasse)
{
        m_craft = schiff;
        m_galax = Milchstrasse;
        m_running = true;
}

void Collision::run()
{
        //algirthm for checking collisions
        cout << "runnnning coll" << endl;
        while(m_running)
        {
                // get the vectors form fighter and galaxis
                m_bullets = m_craft->get_Bullets();
                m_asteorids = m_galax->getAsteorids();
                
                //durchlaufen aller asteorids
                vector<Asteorid*>::iterator asteoridtIt;
                asteoridtIt = m_asteorids.begin();
                while(asteoridtIt != m_asteorids.end())
                {
        	        //durchlafen aller bullets
        	        vector<Bullet*>::iterator bulletIt;
                        bulletIt = m_bullets.begin();
                        while(bulletIt != m_bullets.end())
                        {
                                // if ( (*bulletIt)->getPosition() == (*asteoridtIt)->getPosition() )
                                //                                 {
                                //                                         //getroffen
                                //                                 }
                	        bulletIt++;
                      }
        	        asteoridtIt++;	
                }
                sleep(100);
        }
}

void Collision::stop()
{
        m_running=false;
}