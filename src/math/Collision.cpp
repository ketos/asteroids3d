#include "Collision.hpp"
#include "logic/Game.hpp"

using namespace std;


Collision::Collision()
{
	m_running = true;
   warning = false;
   //m_bullets = 1;
   //m_asteorids = 1;
}

void Collision::run()
{
	//algorithm for checking collisions
   while(m_running)
   {
		radar.clear();
		//delete (&m_bullets);
		//delete (&m_asteorids);
      // get the vectors form fighter and galaxis
      m_bullets = Game::getFighter()->get_Bullets();
      m_asteorids = Game::getGalaxis()->getAsteorids();
      
      //durchlaufen aller asteorids
      vector<Asteorid*>::iterator asteoridtIt;
      asteoridtIt = m_asteorids.begin();
		
		warning = false;

      while(asteoridtIt != m_asteorids.end())
      {
      	(*asteoridtIt)->set_hitable(true);
        	
        	float diffFightX = ((*asteoridtIt)->getPosition())[0] - (Game::getFighter()->getPosition())[0] ;
         float diffFightY = ((*asteoridtIt)->getPosition())[1] - (Game::getFighter()->getPosition())[1] ;
			float diffFightZ = ((*asteoridtIt)->getPosition())[2] - (Game::getFighter()->getPosition())[2] ;
			
         glVector<float> tmp2(diffFightX, diffFightY, diffFightZ);		
			
			int diffFight = sqrt((diffFightX * diffFightX) + (diffFightY * diffFightY) + (diffFightZ * diffFightZ));
			
			if(diffFight > 15000)
			{
				(*asteoridtIt)->changeDirection();
			}
			
			// Das Schiff wird getroffen
			if(diffFight <= (*asteoridtIt)->get_radius())
			{	
				Game::getFighter()->increaseDamage(10);
				(*asteoridtIt)->changeDirection();
				(*asteoridtIt)->destroy();
				sleep(1);
			}
			
			if(diffFight <= 2000)
			{
				warning = true;
			}
			
			/* Für das Radar werden die Asteoriden in einer bestimmten Distanz erfasst */
			diffFightX = (Game::getFighter()->getxAxis()) * tmp2 ;
			diffFightY = (Game::getFighter()->getyAxis()) * tmp2 ;
			diffFightZ = (Game::getFighter()->getzAxis()) * tmp2 ;
			
			glVector<float> *tmp = new glVector<float> (diffFightX, diffFightY, diffFightZ);

			radar.push_back(tmp);
			
			/* Iteration über alle Kugeln, dann berechnen ob ein Asteorid im Hitbereich ist */
			vector<Bullet*>::iterator bulletIt;
         bulletIt = m_bullets.begin();
         while(bulletIt != m_bullets.end())
         {	
            float diffX = ((*bulletIt)->getPosition())[0] - ((*asteoridtIt)->getPosition())[0] ;
            float diffY = ((*bulletIt)->getPosition())[1] - ((*asteoridtIt)->getPosition())[1] ;
				float diffZ = ((*bulletIt)->getPosition())[2] - ((*asteoridtIt)->getPosition())[2] ;
			
				int diff = sqrt((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));               
            
            if ( diff <= (*asteoridtIt)->get_radius())
            {
                	std::cout << (*asteoridtIt)->get_radius() << std::endl;
                	/* Kugel hat den Hitbereich des Asteoriden erreicht und beide werden zerstört */
                	(*bulletIt)->kill();
                	(*asteoridtIt)->destroy();
                	sleep(1);
            }
				bulletIt++;
         }
            
         /* Berechnung der Kollision zwischen zwei Asteoriden */
            
         vector<Asteorid*>::iterator asteoridtIt2;
			asteoridtIt2 = asteoridtIt + 1;
			
			while(asteoridtIt2 != m_asteorids.end())
			{
				float diffAstX = ( ( (*asteoridtIt)->getPosition() )[0] - ( (*asteoridtIt2)->getPosition() )[0] );
				float diffAstY = ( ( (*asteoridtIt)->getPosition() )[1] - ( (*asteoridtIt2)->getPosition() )[1] );
            float diffAstZ = ( ( (*asteoridtIt)->getPosition() )[2] - ( (*asteoridtIt2)->getPosition() )[2] );
                
            int diffAst = sqrt((diffAstX * diffAstX) + (diffAstY * diffAstY) + (diffAstZ * diffAstZ));
                
            (*asteoridtIt2)->set_hitable(true);
            	
            if( ( diffAst <= (*asteoridtIt)->get_radius()  ) || (diffAst <= (*asteoridtIt2)->get_radius() ) )
            {
            	/* Zusammenprall der beiden Asteoriden */

               if( (*asteoridtIt)->is_hitable() )
               {
               	(*asteoridtIt)->changeDirection();
                	(*asteoridtIt)->set_hitable(false);
               }

               if( (*asteoridtIt)->is_hitable() )
               {
               	(*asteoridtIt2)->changeDirection();
                	(*asteoridtIt2)->set_hitable(false);
               }
                	
               sleep(1);
            }
            asteoridtIt2++;
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

bool Collision::getWarning()
{
	return warning;	
}
