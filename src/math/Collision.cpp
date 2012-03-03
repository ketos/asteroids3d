#include "Collision.hpp"
#include "logic/Game.hpp"

using namespace std;


Collision::Collision()
{
	m_running = true;
   	warning = false;
}

void Collision::run()
{
   while(m_running)
   {
   		mutex.lock();
      	/* Asteroiden und Bullets holen */
      	m_bullets = Game::getFighter()->get_Bullets();
      	m_asteorids = Game::getGalaxis()->getAsteorids();

		/* Iterator für die Aseroiden */
      	vector<Asteorid*>::iterator asteoridtIt;
      	asteoridtIt = m_asteorids.begin();

		warning = false;

      	while(asteoridtIt != m_asteorids.end())
      	{
      		/* Differenz zwischen aktuellem Asteoriden und Fighter berechnen */

        	float diffFightX = ((*asteoridtIt)->getPosition())[0] - (Game::getFighter()->getPosition())[0] ;
        	float diffFightY = ((*asteoridtIt)->getPosition())[1] - (Game::getFighter()->getPosition())[1] ;
			float diffFightZ = ((*asteoridtIt)->getPosition())[2] - (Game::getFighter()->getPosition())[2] ;
         	glVector<float> tmp2(diffFightX, diffFightY, diffFightZ);

			int diffFight = sqrt((diffFightX * diffFightX) + (diffFightY * diffFightY) + (diffFightZ * diffFightZ));

			if(diffFight > 15000)
			{
				//(*asteoridtIt)->changeDirection();
			}

			/* Fighter wird getroffen */
			if(diffFight <= (*asteoridtIt)->get_radius())
			{
				if( (*asteoridtIt)->is_mini() )
					Game::getFighter()->increaseDamage(20);
				else
					Game::getFighter()->increaseDamage(50);
				(*asteoridtIt)->destroy();
				sleep(1);
			}

			if(diffFight <= 1000)
			{
				warning = true;
			}

			/* Für das Radar werden die Asteoriden erfasst */
			diffFightX = (Game::getFighter()->getxAxis()) * tmp2 ;
			diffFightY = (Game::getFighter()->getyAxis()) * tmp2 ;
			diffFightZ = (Game::getFighter()->getzAxis()) * tmp2 ;

			glVector<float> *tmp = new glVector<float> (diffFightX, diffFightY, diffFightZ);

			radar2.push_back(tmp);

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
                	/* Kugel hat den Hitbereich des Asteoriden erreicht und beide werden zerstört */
                	(*bulletIt)->kill();
                	(*asteoridtIt)->destroy();
                	sleep(1);
            	}
				++bulletIt;
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

            	if( ( diffAst <= (*asteoridtIt)->get_radius()  ) || (diffAst <= (*asteoridtIt2)->get_radius() ) )
            	{
            		/* Zusammenprall der beiden Asteoriden */
					glVector<float> temp = (*asteoridtIt)->getFlightAxis();
               		(*asteoridtIt)->changeDirection((*asteoridtIt2)->getFlightAxis());
               		(*asteoridtIt)->set_speed(0.1);
               		(*asteoridtIt2)->changeDirection(temp);
               		//(*asteoridtIt2)->set_speed(0.1);
               		sleep(1);
            	}
            	++asteoridtIt2;
			}
			++asteoridtIt;
      }
      radar = radar2;
      radar2.clear();
      mutex.unlock();
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
