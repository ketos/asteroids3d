#include "Galaxis.hpp"
#include "io/Read3DS.hpp"
#include <stdio.h>
#include "math/glVector.hpp"
#include <typeinfo>
#include "io/ReadXML.hpp"
Galaxis::Galaxis()
{
    // create vector for Asteroids
	level = 0;

   	glVector<float> v1(0.0, 0.0, -1000.0);
	glVector<float> v2(0.0, 0.0, 0.0);
	addAsteorid(v1,v2);
	glVector<float> v3(500.0, 0.0, -1000.0);
	glVector<float> v4(0.0, 0.0, 0.0);
	addAsteorid(v3,v4);	
}

void Galaxis::addAsteorid(glVector<float> v1, glVector<float> v2)
{
    Asteorid* a = new Asteorid(v1,v2);;
    Read3DS reader("res/models/asteroid.3ds");
    reader.getMesh(*(static_cast<TexturedMesh*>(a)));
    std::cout << "Neuer Asteorid" << std::endl;
    QObject::connect(a, SIGNAL( destroyed(float, float, float) ), this, SLOT( big_astroid_destroyed(float, float, float) ));
    a->start(); 
    asteorids.push_back( a );
    std::cout << "Fertig hinzugefuegt" << std::endl;
}

void Galaxis::addMiniAsteorid(glVector<float> v1, glVector<float> v2)
{
    Mini_Asteorid* a = new Mini_Asteorid(v1,v2);;
    Read3DS reader("res/models/asteroid.3ds");
    reader.getMesh(*(static_cast<TexturedMesh*>(a)));
    a->start();
    asteorids.push_back( a );
}


void Galaxis::big_astroid_destroyed(float x, float y, float z)
{
	glVector<float> tmp (x,y,z);
	glVector<float> v1 (100,0,0);
	glVector<float> v2 (0,100,0);
	addMiniAsteorid(tmp,v1);
	addMiniAsteorid(tmp,v2);
}

void Galaxis::mini_astroid_destroyed()
{
	std::cout << "Der Slot wurde aufgerufen" << std::endl;
}
    

void Galaxis::render()
{
	//std::cout << asteorids.size() << std::endl;
    if( asteorids.size() > 0 )
    {
      vector<Asteorid*>::iterator asteoridtIt;
      asteoridtIt = asteorids.begin();
      // Iterate over the fighter's bullets and render them
      // if the bullet's lifetime is over, erase it from the vector.
      while(asteoridtIt != asteorids.end()){
	  (*asteoridtIt)->render();
	  //(*asteoridtIt)->info();
	  if(!(*asteoridtIt)->isAlive()){
	      asteoridtIt = asteorids.erase(asteoridtIt);
	      }else{
	        asteoridtIt++;	
	      }
      }
    }
    else
    {
    	//alle asteoriden gelöscht
    	cout << "keine asteoriden"<<endl;
    	nextLevel();
    }
}
/*
void Galaxis::nextLevel()
{
  level++;
  std::cout << "Dies das nächstes Level " << level << std::endl;
    g
void Galaxis::addLevel(string& filename)
{
	//tmp = ReadXML::readConfig( filename );
	/lVector<float> v1(1000.0, 10.0, -1000.0);
    glVector<float> v2(0.0, 0.0, 0.0);
	addAsteorid(v1,v2);
  // XML-Reader liefert pos!!!
  // Iterieren und Asteoriden hinzugefuegen
}
*/
vector<Asteorid*> Galaxis::getAsteorids()
{
    return asteorids;
}

void Galaxis::addLevel(string& filename)
{
	//ReadXML::readConfig( filename);
	//tmp = ReadXML::readConfig( filename );
	m_levels.push_back(ReadXML::readConfig( filename ));
	cout << "blub"<<endl;
}

void Galaxis::nextLevel()
{
	
	cout << m_levels.size()<<endl;
	cout << level <<endl;
	//loeschen aller asteoriden
	//asteorids.clear();
	//naechstes level laden
	//nächtes level in currentLevel
	if (level < m_levels.size())
	{
		cout << "innen"<<endl;
		vector<std::pair<glVector<float>*, glVector<float>* >* >* currentLevel= m_levels[ level ];
	
		vector< std::pair<glVector<float>*, glVector<float>* >* >::iterator levelIt;
		levelIt = currentLevel->begin();
		while( levelIt != currentLevel->end() )
		{
			pair<glVector<float>*, glVector<float>* >* p = (*levelIt);
		    glVector<float> p_1(p->first->x, p->first->y, p->first->z);
		    glVector<float> p_2(p->second->x, p->second->y, p->second->z);
			addAsteorid(p_1, p_2);
			cout << "bla:"<<p->first->x <<endl;
			levelIt++;
    	}
    	//level erhöhen
    	level++;
    }
    else
    {
    	cout<<"ALLE LEVEL DURCH GESPIELT :)) TOLL!"<<endl;
    }
}
