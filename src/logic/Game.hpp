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

/**
*   @brief Die Klasse Game hält alle wichtigen Objekte
*   @brief und bietet statische Schnittstellen um diese zu bekommen.
*/
class Game
{
public:
    /**
    *   @breif Initialisiert alle möglichen Member
	*/
    static void Init();

    /**
    *   @brief Liefert den Fighter zurück
    *   @return der Fighter
    */
    static Fighter* getFighter();
    
    /**
    *   @brief Liefert die Galaxie zurück
    *   @return die Galaxie
    */
    static Galaxis* getGalaxis();

    /**
    *   @brief Liefert die Collision-Instanz zurück
    *   @return die Collision-Instanz
    */
    static Collision* getCollision();

    /**
    *   @brief Liefert die Flug-Emitter-Instanz zurück
    *   @return die Flug-Emitter-Instanz
    */
    static EmitterFlug* getEmitterFlug();

    /**
    *   @brief Liefert das HUD zurück
    *   @return das HUD
    */
    static HUD* getHud();

    /**
    *   @brief Liefert die Punktezahl zurück
    *   @return Punktezahl
    */
    static int getScore();

    /**
    *   @brief Ändert die Punktezahl um das gegebene Delta
    *   @param int delta
    */
    static void changeScore(int change);

    /**
    *   @brief Teilt der Game mit, das ein Game-Over erzeugt wurde
    */
    static void game_over();

    /**
    *   @brief Gibt die aktuelle Perspektive als int zurück
    *   @return int Perspektivennummer
    */
    static int getView();

    /**
    *   @brief Setzt die Perspektive
    *   @param int Perspektivennummer
    */
    static void setView(int view);
    
    /*
     *  @brief if the fighter has shot
     *  @return true if the fighter shoots
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
    *   @brief Setze Level auf 1
    */
    static void reset_level();

    /**
    *   @brief Setze Punkte auf 0
    */
    static void reset_score();

    /**
    *   @brief Teilt der Game mit, dass geschossen wurde
    */
    static void shot();

    /**
    *   @brief Fragt ob wieder geschossen werden darf
    *   @return Ob geschossen werden darf
    */
    static bool getshoot(); 

    /**
    *   @brief Updatet reloadtimer und sorgt fuer traegheit des schiffes
    */
    static void update();
    
    /**
    *   @brief  Gibt den Explsionsemitter zurueck
    *   @return ExplosionsEmitter
    */
    static EmitterExplosion* getEEmit();

private:
    /**
    *   @breif Alle Instanz-Member
    */
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

    /**
    *   @brief Lädt das angegebene Modell für den Fighter
    *   @param string Dateiname der Modelldatei
    */
    static void loadFighter(string filename);
};

#endif 
