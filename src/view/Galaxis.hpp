#ifndef __GALAXIS_HPP__
#define __GALAXIS_HPP__

#include "rendering/Asteorid.hpp"
#include <vector>

class Galaxis{
  
      public:
	      Galaxis();
	      
	      void addAsteorid(glVector<float> v1, glVector<float> v2);
	      
	      void render();
	      
	      vector<Asteorid*> getAsteorids();
	      
      private:
	      vector<Asteorid*> asteorids;
};

#endif
