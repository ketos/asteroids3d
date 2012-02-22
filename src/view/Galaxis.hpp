#ifndef __GALAXIS_HPP__
#define __GALAXIS_HPP__

#include "rendering/Asteorid.hpp"
#include <vector>
using namespace std;
class Galaxis{
  
      public:
	      Galaxis();
	      
	      void addAsteorid(glVector<float> v1, glVector<float> v2);
	      
	      void render();
//               void killAsteorid(Asteorid* g);
	      vector<Asteorid*> getAsteorids();
	      void nextLevel();
	      
      private:
	      vector<Asteorid*> asteorids;
	      vector<pair<glVector<float>,glVector<float> > > pos;
	      int level;
};

#endif
