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
int i = 0;
        //algirthm for checking collisions
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

			float diffFightX = fabs( ((*asteoridtIt)->getPosition())[0] - (m_craft->getPosition())[0] );
                        float diffFightY = fabs( ((*asteoridtIt)->getPosition())[1] - (m_craft->getPosition())[1] );
			float diffFightZ = fabs( ((*asteoridtIt)->getPosition())[2] - (m_craft->getPosition())[2] );
			
			

			if(diffFightX <= 100 && diffFightY <= 100 && diffFightZ <= 100)
			{
				cout << "Fighter trifft asteorid!" << i << endl;
				(*asteoridtIt)->changeDirection();
				m_craft->increaseDamage(50);
			}


        	        //durchlafen aller bullets
        	        vector<Bullet*>::iterator bulletIt;
                        bulletIt = m_bullets.begin();
                        while(bulletIt != m_bullets.end())
                        {
				
                                float diffX = fabs( ((*bulletIt)->getPosition())[0] - ((*asteoridtIt)->getPosition())[0] );
                                float diffY = fabs( ((*bulletIt)->getPosition())[1] - ((*asteoridtIt)->getPosition())[1] );
                                float diffZ = fabs( ((*bulletIt)->getPosition())[2] - ((*asteoridtIt)->getPosition())[2] );
                                
                                if ( (diffX <= 100) && (diffY <= 100) && (diffZ <= 100) )
                                {
                                        //getroffen
                                        //cout << "diffx:"<<diffX<<"  diffY:"<< diffY << "  diffZ:"<<diffZ<<endl;
                                        
                                        //auflösen der Kugel 
                                        (*bulletIt)->kill();
                                        //m_bullets.erase(bulletIt);
                                        //auflösen des planeten
                                        (*asteoridtIt)->destroy();
                                        //m_asteorids.erase(asteoridtIt);
                                        
                                }
                	        bulletIt++;
				
				vector<Asteorid*>::iterator asteoridtIt2;
				asteoridtIt2 = asteoridtIt + 1;
				while(asteoridtIt2 != m_asteorids.end())
				{
					float diffAstX = fabs( ((*asteoridtIt)->getPosition())[0] - ((*asteoridtIt2)->getPosition())[0] );
					float diffAstY = fabs( ((*asteoridtIt)->getPosition())[1] - ((*asteoridtIt2)->getPosition())[1] );
                               		float diffAstZ = fabs( ((*asteoridtIt)->getPosition())[2] - ((*asteoridtIt2)->getPosition())[2] );

					if((diffAstX <= 100) && (diffAstY <= 100) && (diffAstZ <= 100))
					{
						//stoss methode an asteoriden aufrufen
						cout << "zwei Asteoriden stossen sich ab..." << endl;
						(*asteoridtIt)->changeDirection();
						(*asteoridtIt2)->changeDirection();
					}
				}			
                      }
        	        asteoridtIt++;	
                }
                usleep(1000);
        }
}

void Collision::stop()
{
        m_running=false;
}
bool Collision::isRunning()
{
        return m_running;
}