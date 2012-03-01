#ifndef __GAME_H_
#define __GAME_H_

#include "view/Galaxis.hpp"
#include "math/Collision.hpp"
#include "rendering/Fighter.hpp"
#include "rendering/partikel/Emitter-Flug.hpp"
#include "view/HUD.hpp"
#include "io/SoundManager.hpp"

class Game
{
public:
    
    static void Init();

    static Fighter* getFighter();
private:
    static void loadFighter(string filename);
public:
    static Galaxis* getGalaxis();

    static Collision* getCollision();

    static EmitterFlug* getEmitterFlug();

    static HUD* getHud();

    static int getScore();
    static void changeScore(int change);
    
    static int getView();
    static void setView(int view);
    /*
     * @brief if the fighter has shot
     * @return true if the fighter shot
     */ 
    static bool wasShot();
    static int getLevel();
    static void incLevel();
    static void reset_level();
    static void reset_score();
    static void shot();
    static bool getshoot(); 
    static void update();

private:
    static Fighter  m_fighter;
    static Galaxis  m_galaxis;
    static Collision   m_coll;
    static EmitterFlug m_Femit;
    static HUD m_Hud;
    
    static bool m_shoot;
    static int i;
    
    static int m_points;
    static int m_level;
    static int m_view;
};

#endif 
