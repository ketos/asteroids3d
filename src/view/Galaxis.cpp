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
	// Connects Signal and Slot with this Asteorid
    QObject::connect(a, SIGNAL( destroyed(float, float, float) ), this, SLOT( big_astroid_destroyed(float, float, float) ));
    a->start();
    asteorids.push_back( a );
}

void Galaxis::addMiniAsteorid(glVector<float> v1, glVector<float> v2)
{
    Mini_Asteorid* a = new Mini_Asteorid(v1,v2);
    Read3DS reader("res/models/asteroid.3ds");
    reader.getMesh(*(static_cast<TexturedMesh*>(a)));
	// Connects Signal and Slot with this Asteorid
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
	// Increase Score and create three new little Asteorids instead of the big one.
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
    if( !asteorids.empty() )
    {
        vector<Asteorid*>::iterator asteoridtIt;
        asteoridtIt = asteorids.begin();
        // Iterate over Asteorids and render them
        while(asteoridtIt != asteorids.end()){
	        (*asteoridtIt)->render();
	        if(!(*asteoridtIt)->isAlive()){
	            asteoridtIt = asteorids.erase(asteoridtIt);
	        }
	        else
	        {
	            ++asteoridtIt;
	        }
        }
    }
    else
    {
		// All Asteorids destroyed, reset Level and Fighter Position
    	Game::getFighter()->reset_position();
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
	if (level < m_levels.size())
	{
		// Get Level Information of current level
		vector<std::pair<glVector<float>*, glVector<float>* >* >* currentLevel = m_levels[ level ];
		vector< std::pair<glVector<float>*, glVector<float>* >* >::iterator levelIt;
		levelIt = currentLevel->begin();
		while( levelIt != currentLevel->end() )
		{
			// Iterate over Levelinformation and add new Asteorids
			pair<glVector<float>*, glVector<float>* >* p = (*levelIt);
		   	glVector<float> p_1(p->first->x, p->first->y, p->first->z);
		   	glVector<float> p_2(p->second->x, p->second->y, p->second->z);
			addAsteorid(p_1, p_2);
			++levelIt;
    	}
    	level++;
    	paintLevel = true;
    }
}

bool Galaxis::shouldIncLevel()
{
	if ((paintLevelcount < 100) && (paintLevelcount > 0) )
	{
			// Draw Level on HUD
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
