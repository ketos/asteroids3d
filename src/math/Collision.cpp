#include "Collision.hpp"
#include <iostream>
#include <math.h>

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
                                float diffX = fabs( ((*bulletIt)->getPosition())[0] - ((*asteoridtIt)->getPosition())[0] );
                                float diffY = fabs( ((*bulletIt)->getPosition())[1] - ((*asteoridtIt)->getPosition())[1] );
                                float diffZ = fabs( ((*bulletIt)->getPosition())[2] - ((*asteoridtIt)->getPosition())[2] );
                                if ( (diffX <= 1000) && (diffY <= 1000) && (diffZ <= 1000) )
                                {
                                        //getroffen
                                        cout << endl << "Kugel Ast getroffen" << endl;
                                }
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