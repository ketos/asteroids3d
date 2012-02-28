#ifndef __GALAXIS_HPP__
#define __GALAXIS_HPP__

#include "rendering/Asteorid.hpp"
#include "rendering/Mini_Asteorid.hpp"
#include "io/Read3DS.hpp"
#include "math/glVector.hpp"
#include "io/ReadXML.hpp"
#include "view/HUD.hpp"

#include <vector>
#include <QObject>
#include <string>
#include <stdio.h>
#include <typeinfo>


using namespace std;

class Galaxis: public QObject
{
	Q_OBJECT
	
     public:
	    	Galaxis();
	    	void addAsteorid(glVector<float> v1, glVector<float> v2);
	    	void render();
	    	vector<Asteorid*> getAsteorids(); 
			void addMiniAsteorid(glVector<float> v1, glVector<float> v2);
			void addLevel(string& filename);
			void nextLevel();
			glVector<float> getOneAsteoridPosition();

			bool shouldIncLevel();
			int getLevelnumber();
    	private:
	    	vector<Asteorid*> asteorids;
	    	vector<pair<glVector<float>,glVector<float> > > pos;
	     	int level;
	     	bool paintLevel;
	     	vector< vector<std::pair<glVector<float>*, glVector<float>* >* >* > m_levels;
	     	vector<std::pair<glVector<float>*, glVector<float>* >* > tmp;
	     	
	     	int paintLevelcount;
	     	HUD* display;
	     	
	public slots:

		void big_astroid_destroyed(float x, float y, float z);
		void mini_astroid_destroyed();
};

#endif
