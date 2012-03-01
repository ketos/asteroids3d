#include "logic/Game.hpp"

Fighter Game::m_fighter;
Galaxis Game::m_galaxis;
Collision Game::m_coll;
EmitterFlug Game::m_Femit;
HUD Game::m_Hud;

int Game::m_points = 0;
int Game::m_level = 1;
int Game::m_view = 0;
bool Game::m_shoot;
int Game::i = 0;

void Game::Init()
{
    loadFighter("res/models/bearcat.3ds");
    m_Femit.setMaxPartikel(100);
	
    for(;m_level < 8;incLevel())
    {
    	std::string str1 = "res/config/level";
		std::string str2 = ".xml";

    	std::stringstream oss;
    	oss << str1 << m_level << str2;

    	std::string level = oss.str();    

		getGalaxis()->addLevel( level );	
    }
    m_shoot = true;
}

Fighter* Game::getFighter()
{
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
    return (&m_galaxis);
}

Collision* Game::getCollision()
{
    return (&m_coll);
}

EmitterFlug* Game::getEmitterFlug()
{
    return (&m_Femit);
}

HUD* Game::getHud()
{
    return (&m_Hud);
}

int Game::getScore()
{
    return m_points;
}
bool Game::wasShot()
{
	return 	m_fighter.wasShot();
}
void Game::changeScore(int change)
{
    m_points += change;
}

int Game::getLevel()
{
    return m_level;
}
void Game::incLevel()
{
    m_level++;
}
int Game::getView()
{
    return m_view;
}
void Game::setView(int view)
{
    m_view = view;
}
void Game::shot()
{
    m_shoot = false;
}
bool Game::getshoot()
{
    return m_shoot;
}
void Game::update()
{
    //winkel verkleinern
    m_fighter.reduceAngle();
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