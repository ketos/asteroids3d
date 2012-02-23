#include "Galaxis.hpp"
#include "io/Read3DS.hpp"
#include <stdio.h>
#include "math/glVector.hpp"
#include <typeinfo>

Galaxis::Galaxis()
{
    // create vector for Asteroids
	level = 0;
   glVector<float> v1(0.0, 0.0, -1000.0);
	glVector<float> v2(0.0, 0.0, 0.0);
	addMiniAsteorid(v1,v2);
	
}

void Galaxis::addAsteorid(glVector<float> v1, glVector<float> v2)
{
    Asteorid* a = new Asteorid(v1,v2);;
    Read3DS reader("asteroid.3ds");
    reader.getMesh(*(static_cast<TexturedMesh*>(a)));
    // Start a new thread, move the bullet
    a->start();
    // Add it to this fighter's vector of bullets    
    asteorids.push_back( a );
}

void Galaxis::addMiniAsteorid(glVector<float> v1, glVector<float> v2)
{
    Mini_Asteorid* a = new Mini_Asteorid(v1,v2);;
    Read3DS reader("asteroid.3ds");
    reader.getMesh(*(static_cast<TexturedMesh*>(a)));
    // Start a new thread, move the bullet
    a->start();
    // Add it to this fighter's vector of bullets    
    asteorids.push_back( a );
}
	      
void Galaxis::render()
{
    if(asteorids.empty())
        nextLevel();
    if( asteorids.size() > 0 )
    {
      vector<Asteorid*>::iterator asteoridtIt;
      asteoridtIt = asteorids.begin();
      // Iterate over the fighter's bullets and render them
      // if the bullet's lifetime is over, erase it from the vector.
      while(asteoridtIt != asteorids.end()){
	  (*asteoridtIt)->render();
	  (*asteoridtIt)->info();
	  if(!(*asteoridtIt)->isAlive()){
	      asteoridtIt = asteorids.erase(asteoridtIt);
	      }else{
	        asteoridtIt++;	
	      }
      }
    }
}

void Galaxis::nextLevel()
{
  level++;
  std::cout << "Dies das nächstes Level " << level << std::endl;
    glVector<float> v1(1000.0, 10.0, -1000.0);
    glVector<float> v2(0.0, 0.0, 0.0);
	addAsteorid(v1,v2);
  // XML-Reader liefert pos!!!
  // Iterieren und Asteoriden hinzugefuegen
}

vector<Asteorid*> Galaxis::getAsteorids()
{
    return asteorids;
}

