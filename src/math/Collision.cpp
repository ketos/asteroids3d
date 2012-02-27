#include "Collision.hpp"

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
        while(m_running)
        {
		radar.clear();

        // get the vectors form fighter and galaxis
        m_bullets = m_craft->get_Bullets();
        m_asteorids = m_galax->getAsteorids();
      
        //durchlaufen aller asteorids
        vector<Asteorid*>::iterator asteoridtIt;
        asteoridtIt = m_asteorids.begin();
		


       	while(asteoridtIt != m_asteorids.end())
        {
        	float diffFightX = ((*asteoridtIt)->getPosition())[0] - (m_craft->getPosition())[0] ;
            float diffFightY = ((*asteoridtIt)->getPosition())[1] - (m_craft->getPosition())[1] ;
			float diffFightZ = ((*asteoridtIt)->getPosition())[2] - (m_craft->getPosition())[2] ;
			//std::cout << "fx:"<<(m_craft->getPosition())[0]<<",y:"<<(m_craft->getPosition())[1]<<",z:"<<(m_craft->getPosition())[2]<<std::endl;
			//std::cout << "ax:"<<((*asteoridtIt)->getPosition())[0]<<",y:"<<((*asteoridtIt)->getPosition())[1]<<",z:"<<((*asteoridtIt)->getPosition())[2]<<std::endl;
            glVector<float> tmp2(diffFightX, diffFightY, diffFightZ);		
			
			int diffFight = sqrt((diffFightX * diffFightX) + (diffFightY * diffFightY) + (diffFightZ * diffFightZ));
			
			if(diffFight > 4100)
			{
				//(*asteoridtIt)->changeDirection();
			}
			
			// Das Schiff wird getroffen
			if(diffFightX <= 100 && diffFightY <= 100 && diffFightZ <= 100)
			{
				std::cout << "Das Schiff nimmt Schaden" << std::endl;
				m_craft->increaseDamage(10);
				(*asteoridtIt)->changeDirection();
				sleep(1);
			}
			
			/* Für das Radar werden die Asteoriden in einer bestimmten Distanz erfasst */
			if(diffFight < 5000)
			{
                //std::cout << "fax:"<<diffFightX<<",y:"<<diffFightY<<",z:"<<diffFightZ<<std::endl;
				diffFightX = (m_craft->getxAxis()) * tmp2 ;
				diffFightY = (m_craft->getyAxis()) * tmp2 ;
				diffFightZ = (m_craft->getzAxis()) * tmp2 ;
				glVector<float> *tmp = new glVector<float> (diffFightX, diffFightY, diffFightZ);
				
				radar.push_back(tmp);
			}
			
			/* Iteration über alle Kugeln, dann berechnen ob ein Asteorid im Hitbereich ist */
			vector<Bullet*>::iterator bulletIt;
            bulletIt = m_bullets.begin();
            while(bulletIt != m_bullets.end())
            {	
            	float diffX = fabs( ((*bulletIt)->getPosition())[0] - ((*asteoridtIt)->getPosition())[0] );
          		float diffY = fabs( ((*bulletIt)->getPosition())[1] - ((*asteoridtIt)->getPosition())[1] );
                float diffZ = fabs( ((*bulletIt)->getPosition())[2] - ((*asteoridtIt)->getPosition())[2] );               
                if ( (diffX <= 100) && (diffY <= 100) && (diffZ <= 100) )
                {
                	/* Kugel hat den Hitbereich des Asteoriden erreicht und beide werden zerstört */
                	(*bulletIt)->kill();
                	(*asteoridtIt)->destroy();
                	sleep(1);
                	// --> Richtig unschön!!
              	}
				bulletIt++;
            }
            
			asteoridtIt++;	
           	}
          	usleep(1000);
        }
}

vector<glVector<float>*> Collision::getCollisionVector()
{
	return radar;
}

void Collision::stop()
{
        m_running = false;
}
bool Collision::isRunning()
{
        return m_running;
}
