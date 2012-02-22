#include "Galaxis.hpp"
#include "io/Read3DS.hpp"
#include <stdio.h>
Galaxis::Galaxis()
{
    // create vector for Asteroids
}

void Galaxis::addAsteorid(glVector<float> v1, glVector<float> v2)
{
    Asteorid* a = new Asteorid(v1,v2);
	Read3DS reader("arrow.3ds");
    reader.getMesh(*(static_cast<TexturedMesh*>(a)));
    // Start a new thread, move the bullet
	a->start();
    // Add it to this fighter's vector of bullets
    std::cout << "Asteoriden hinzugefuegt" << std::cout;  
    asteorids.push_back( a );
}
	      
void Galaxis::render()
{
    if( asteorids.size() > 0 )
    {
     std::cout << "rendere den asteoriden" << std::cout;   
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
}

vector<Asteorid*> Galaxis::getAsteorids()
{
    return asteorids;
}