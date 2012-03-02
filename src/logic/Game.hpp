/**
*   @file Game.hpp
*   @author gruppe3
*/

#ifndef __GAME_H_
#define __GAME_H_

#include "view/Galaxis.hpp"
#include "math/Collision.hpp"
#include "rendering/Fighter.hpp"
#include "rendering/partikel/Emitter-Flug.hpp"
#include "rendering/partikel/Emitter-Explosion.hpp"
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
    static void game_over();
    static int getView();
    static void setView(int view);
    
    /*
     * @brief if the fighter has shot
     * @return true if the fighter shoots
     */ 
    static bool wasShot();

    /**
    *   @brief Liefert aktuelle level zurueck
    *   @return Levelnummer
    */
    static int getLevel();
    
    /**
    *   @brief Erhoet das level um 1
    */
    static void incLevel();

    /**
    *   @brief
    */
    static void reset_level();

    /**
    *   @brief
    */
    static void reset_score();

    /**
    *   @brief
    */
    static void shot();

    /**
    *   @brief
    */
    static bool getshoot(); 

    /**
    *   @brief
    */
    static void update();
    
    /**
    *   @brief
    */
    static EmitterExplosion* getEEmit();

private:
    static Fighter  m_fighter;
    static Galaxis  m_galaxis;
    static Collision   m_coll;
    static EmitterFlug m_Femit;
    static HUD m_Hud;

    static EmitterExplosion m_eemit;
    
    static bool m_shoot;
    static int i;
    
    static int m_points;
    static int m_level;
    static int m_view;
};

#endif 
