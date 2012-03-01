#include "Galaxis.hpp"
#include "logic/Game.hpp"

Galaxis::Galaxis()
{
	level           = 0;
	nextLevel();
	paintLevel      = false;
   	paintLevelcount = 0;
}

void Galaxis::addAsteorid(glVector<float> v1, glVector<float> v2)
{
    Asteorid* a = new Asteorid(v1,v2);
    Read3DS reader("res/models/asteroid2.3ds");
    reader.getMesh(*(static_cast<TexturedMesh*>(a)));
    QObject::connect(a, SIGNAL( destroyed(float, float, float) ), this, SLOT( big_astroid_destroyed(float, float, float) ));
    a->start();
    asteorids.push_back( a );
}

void Galaxis::addMiniAsteorid(glVector<float> v1, glVector<float> v2)
{
    Mini_Asteorid* a = new Mini_Asteorid(v1,v2);
    Read3DS reader("res/models/asteroid.3ds");
    reader.getMesh(*(static_cast<TexturedMesh*>(a)));
    QObject::connect(a, SIGNAL( hit() ), this, SLOT(mini_astroid_destroyed() ) );
    a->start();
    asteorids.push_back( a );
}


void Galaxis::big_astroid_destroyed(float x, float y, float z)
{
	Game::changeScore(50);
	glVector<float> tmp (x,y,z);
	glVector<float> v1 (  ( (rand() % 200 - 100)), ( (rand() % 200 - 100)), ( (rand() % 200 - 100) ) );
	glVector<float> v2 (  ( (rand() % 200 - 100)), ( (rand() % 200 - 100)), ( (rand() % 200 - 100) ) );
	glVector<float> v3 (  ( (rand() % 200 - 100)), ( (rand() % 200 - 100)), ( (rand() % 200 - 100) ) );
	
	addMiniAsteorid(tmp, v1);
	addMiniAsteorid(tmp, v2);
	addMiniAsteorid(tmp, v3);
}

void Galaxis::mini_astroid_destroyed()
{
	Game::changeScore(20);
}

void Galaxis::render()
{
    if( asteorids.size() > 0 )
    {
      vector<Asteorid*>::iterator asteoridtIt;
      asteoridtIt = asteorids.begin();
      // Iterate over the fighter's bullets and render them
      // if the bullet's lifetime is over, erase it from the vector.
      while(asteoridtIt != asteorids.end()){
	  (*asteoridtIt)->render();
	  if(!(*asteoridtIt)->isAlive()){
	      asteoridtIt = asteorids.erase(asteoridtIt);
	      }else{
	        asteoridtIt++;	
	      }
      }
    }
    else
    {
    	Game::getFighter()->reset_position();
    	//alle asteoriden gelöscht
    	nextLevel();
   }
}

vector<Asteorid*> Galaxis::getAsteorids()
{
   return asteorids;
}

glVector<float> Galaxis::getOneAsteoridPosition()
{
   vector<Asteorid*>::iterator asteoridtIt;
   asteoridtIt = asteorids.begin();
   return (*asteoridtIt)->getPosition();
}

void Galaxis::addLevel(string& filename)
{
	m_levels.push_back(ReadXML::readConfig( filename ));
}

void Galaxis::nextLevel()
{
	//loeschen aller asteoriden
	//asteorids.clear();
	//naechstes level laden
	//nächtes level in currentLevel
	if (level < m_levels.size())
	{
		vector<std::pair<glVector<float>*, glVector<float>* >* >* currentLevel = m_levels[ level ];
		vector< std::pair<glVector<float>*, glVector<float>* >* >::iterator levelIt;
		levelIt = currentLevel->begin();
		while( levelIt != currentLevel->end() )
		{
			pair<glVector<float>*, glVector<float>* >* p = (*levelIt);
		   	glVector<float> p_1(p->first->x, p->first->y, p->first->z);
		   	glVector<float> p_2(p->second->x, p->second->y, p->second->z);
			addAsteorid(p_1, p_2);
			levelIt++;
    	}
    	level++;
    	paintLevel = true;
    }
    else
    {
    }
}

bool Galaxis::shouldIncLevel()
{
	if ((paintLevelcount < 100) && (paintLevelcount > 0) )
	{
			paintLevel = true;
	}
	
   if (paintLevel)
	{
	   paintLevelcount++;
		paintLevel = false;
		return true;
	}
	paintLevelcount = 0;
	paintLevel      = false;
	return false;
}

int Galaxis::getLevelnumber()
{
	return level;	
}

void Galaxis::reset_level()
{
	level = 0;
	asteorids.clear();
}
