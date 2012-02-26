#ifndef __GALAXIS_HPP__
#define __GALAXIS_HPP__

#include "rendering/Asteorid.hpp"

#include "rendering/Mini_Asteorid.hpp"

#include <vector>

#include <QObject>

#include <string>

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
			int getScore();
			
    	private:
	    	vector<Asteorid*> asteorids;
	    	vector<pair<glVector<float>,glVector<float> > > pos;
	     	int level;
	     	vector< vector<std::pair<glVector<float>*, glVector<float>* >* >* > m_levels;
	     	vector<std::pair<glVector<float>*, glVector<float>* >* > tmp;
	     	
	     	//lager mch aus
	     	int score;
	     	
	public slots:

		void big_astroid_destroyed(float x, float y, float z);
		void mini_astroid_destroyed();
};

#endif
