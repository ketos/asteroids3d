#include "logic/Game.hpp"

Fighter Game::m_fighter;
Galaxis Game::m_galaxis;
Collision Game::m_coll;
EmitterFlug Game::m_Femit;
HUD Game::m_Hud;

int Game::m_points = 0;
int Game::m_level = 0;

void Game::Init()
{
    loadFighter("res/models/bearcat.3ds");
}

Fighter* Game::getFighter()
{
    return (&m_fighter);
}

void Game::loadFighter(string filename)
{
	// Load new model
   // Fighter m_fighter();
	//m_fighter = new Fighter();
	Read3DS reader(filename.c_str());
	reader.getMesh(*(static_cast<TexturedMesh*>(&m_fighter)));
}
bool Game::isFighter()
{
    return ((&m_fighter) != 0);
}
void Game::delFighter()
{
    delete (&m_fighter);
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
