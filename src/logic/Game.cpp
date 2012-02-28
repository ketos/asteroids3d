#include "logic/Game.hpp"

Fighter Game::m_fighter;
Galaxis Game::m_galaxis;
Collision Game::m_coll;
EmitterFlug Game::m_Femit;
HUD Game::m_Hud;

int Game::m_points = 0;
int Game::m_level = 0;

void Init()
{

}

Fighter* Game::getFighter()
{
    return (&m_fighter);
}
void Game::setFighter(Fighter fighter)
{
    m_fighter = fighter;
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
