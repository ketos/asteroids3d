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
        	float diffFightX = fabs( ((*asteoridtIt)->getPosition())[0] - (m_craft->getPosition())[0] );
            float diffFightY = fabs( ((*asteoridtIt)->getPosition())[1] - (m_craft->getPosition())[1] );
			float diffFightZ = fabs( ((*asteoridtIt)->getPosition())[2] - (m_craft->getPosition())[2] );
			
			int diffFight = sqrt((diffFightX * diffFightX) + (diffFightY * diffFightY) + (diffFightZ * diffFightZ));
			
			if(diffFight > 15000)
			{
				(*asteoridtIt)->changeDirection();
			}
			
			// Das Schiff wird getroffen
			if(diffFightX <= 200 && diffFightY <= 200 && diffFightZ <= 200)
			{
				m_craft->increaseDamage(10);
				(*asteoridtIt)->changeDirection();
				
				(*asteoridtIt)->destroy();
				sleep(1);
			}
			
			/* Für das Radar werden die Asteoriden in einer bestimmten Distanz erfasst */
			if(diffFight < 15000)
			{
				diffFightX = (m_craft->getxAxis()) * ((*asteoridtIt)->getPosition()) ;
				diffFightY = (m_craft->getyAxis()) * ((*asteoridtIt)->getPosition()) ;
				diffFightZ = (m_craft->getzAxis()) * ((*asteoridtIt)->getPosition()) ;
				glVector<float> *tmp = new glVector<float> (diffFightX, diffFightZ, diffFightY);
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
