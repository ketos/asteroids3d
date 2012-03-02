/**
*   @file Game.cpp
*   @author gruppe3
*/
#include "logic/Game.hpp"

//init all static members
Fighter Game::m_fighter;
Galaxis Game::m_galaxis;
Collision Game::m_coll;
EmitterFlug Game::m_Femit;
HUD Game::m_Hud;
EmitterExplosion Game::m_eemit;

int Game::m_points = 0;
int Game::m_level = 1;
int Game::m_view = 0;
bool Game::m_shoot;
int Game::i = 0;

void Game::Init()
{
    //load fighter modell
    loadFighter("res/models/bearcat.3ds");
    m_Femit.setMaxPartikel(100);

    //load all 7 Levels
    std::string file_prefix = "res/config/level";
	std::string file_postfix = ".xml";	

    for(;m_level < 8;incLevel())
    {
    	std::stringstream oss;
    	oss << file_prefix << m_level << file_postfix;

    	std::string level = oss.str();    

		getGalaxis()->addLevel( level );	
    }

    //we can shoot
    m_shoot = true;
}

Fighter* Game::getFighter()
{
    //return pointer to fighter
    return (&m_fighter);
}

void Game::loadFighter(string filename)
{
	// Load new model
	Read3DS reader(filename.c_str());
	reader.getMesh(*(static_cast<TexturedMesh*>(&m_fighter)));
}

Galaxis* Game::getGalaxis()
{
    //return pointer to galaxis
    return (&m_galaxis);
}

Collision* Game::getCollision()
{
    //return pointer to collision
    return (&m_coll);
}

EmitterFlug* Game::getEmitterFlug()
{
    //return pointer to EmitterFlug
    return (&m_Femit);
}

HUD* Game::getHud()
{
    //return pointer to HUD
    return (&m_Hud);
}

void Game::game_over()
{
    //reset fighter damage, position.
	getFighter()->resetDamage();
	getFighter()->reset_position();
    
    /reset level and score
    getGalaxis()->reset_level();
	reset_score();
}

int Game::getScore()
{
    //return the score
    return m_points;
}
bool Game::wasShot()
{
    //return if the fighter was shot
	return 	m_fighter.wasShot();
}
void Game::changeScore(int change)
{
    //change score 
    m_points += change;
}

void Game::reset_level()
{
    //reset level to 1
	m_level = 1;
}

void Game::reset_score()
{
    //reset points to 0
	m_points = 0;
}

int Game::getLevel()
{
    //return current levelnumber
    return m_level;
}
void Game::incLevel()
{
    //increment levelnumber
    m_level++;
}
int Game::getView()
{
    //return perspective
    return m_view;
}
void Game::setView(int view)
{
    //set perspective
    m_view = view;
}
void Game::shot()
{
    //we cannot shoot now
    m_shoot = false;
}
bool Game::getshoot()
{
    //return if we can shoot
    return m_shoot;
}
void Game::update()
{
    //winkel verkleinern
    m_fighter.reduceAngle();

    //cooldown der schüsse aktualisieren
    if(!m_shoot)
    {
        if(i>10)
        {
            m_shoot = true;
            i = 0;
        }
        i++;
    }
}

EmitterExplosion* Game::getEEmit()
{
    //return pointer to ExplosionEmitter
    return &m_eemit;
}

