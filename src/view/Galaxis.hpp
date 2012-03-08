/**
 *  @file Galaxis.hpp
 *  @author gruppe3
 */

#ifndef __GALAXIS_HPP__
#define __GALAXIS_HPP__

#include <vector>
#include <QObject>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>

#include "io/Read3DS.hpp"
#include "io/ReadXML.hpp"
#include "math/glVector.hpp"
#include "rendering/Asteorid.hpp"
#include "rendering/Mini_Asteorid.hpp"
#include "view/HUD.hpp"

using namespace std;

/*
 * @brief Galaxis Class, to manage Asteorids
 */
class Galaxis: public QObject
{
Q_OBJECT
	
public:
    /*
     * @brief Constructs a Galaxis
     */
    Galaxis();
    /*
     * @brief Adds a Asteorid to the Galaxis
     * @param v1 Position of Asteorid
     * @param v2 Direction of Asteorid
     */
    void addAsteorid(glVector<float> v1, glVector<float> v2);
	/*
	 * @brief Renders the Galaxis
	 */
    void render();
	/*
	 * @brief Returns the Asteorids of the Galaxis
	 * @return List of all Asteorids
	 */
    vector<Asteorid*> getAsteorids(); 
	/*
	 * @brief Adds a little Asteorid to Galaxis
	 * @param v1 Position of Asteorid
	 * @param v2 Direction of Asteorid
	 */
    void addMiniAsteorid(glVector<float> v1, glVector<float> v2);
	/*
	 * @brief Add Level Information
	 * @param filename String who represents the Level
	 */
    void addLevel(string& filename);
	/*
	 * @brief Tells that the Galaxis has to load the next Level
	 */
    void nextLevel();
	/*
	 * @brief Get the Position of One Asteotrid
	 * @return Position of one Asteorid
	 */
    glVector<float> getOneAsteoridPosition();
	/*
	 * @brief Resets the Galaxis to Level 1
	 */
	void reset_level();
	/*
	 * @brief Level has to be increased
	 */
    bool shouldIncLevel();
	/*
	 * @brief Gets the Number of the actual Level
	 */
    int getLevelnumber();

private:
	/*
	 * @brief Vector of all Asteorids
	 */
    vector<Asteorid*> asteorids;
	/*
	 * @brief Vector which contains Pairs with Information about Pos. and Direction of Asteorids
	 */
    vector<pair<glVector<float>,glVector<float> > > pos;
	/*
	 * @brief Level
	 */
    unsigned int level;
	/*
	 * @brief Should the Level painted
	 */
    bool paintLevel;
	/*
	 * @brief Verctor who saves the Levelinformation
	 */
    vector< vector<std::pair<glVector<float>*, glVector<float>* >* >* > m_levels;
	/*
	 * @brief Tempoäre Variable
	 */
    vector<std::pair<glVector<float>*, glVector<float>* >* > tmp;
	/*
	 * @brief Counts who often the Levelcounter has been painted
	 */
    int paintLevelcount;
	/*
	 * @brief Instance of HUD
	 */
    HUD* display;
	     	
public slots:
	/*
	 * @brief Called, if Big Asteorid is destroyed
	 */
    void big_astroid_destroyed(float x, float y, float z);
	/*
	 * @brief Called, if little Asteorid is destroyed
	 */
    void mini_astroid_destroyed();
};

#endif
