/**
 * @file HUD.hpp
 *
 * @author gruppe3
 */
#ifndef _HUD_H
#define _HUD_H

#include <QBrush>
#include <QFont>
#include <QImage>
#include <QPen>
#include <QGLWidget>
#include <QString>
#include <QFontMetrics>
#include <QPushButton>
#include <QFile>
#include <QTextStream>

#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <string.h>

#include "io/ReadTXT.hpp"
#include "math/glVector.hpp"


/**
*   @brief Realisiert ein HUD Overlay
*
*/
class HUD
{
public:
  /**
  	*@brief Defualt Constructor
  	*/
  	HUD();

    ~HUD();

  /**
   * @brief Draws the HUD
   * @param x width of the window;
   * @param y hiegth of the window;
   * @param f Used Font
   */
  void draw(int x ,int y, QFont f);

  /**
   *@brief Draws the given Astroid on the radar
   *@param vec the Astroid position
   *@param radarrange the max distance for astroids
   *@param durchmesser diameter of the radar
   *@param radarmidx x value of the radarmid
   *@param radarmidy y value of the radarmid
   */
  void drawRadarAstroid(glVector<float>* vec, float radarrange, int durchmesser, int radarmidx, int radarmidy);

  /**
   *@brief sets the collvec which contains the astroids in Radarrange
   *@param collvec vector with astroids in radarrange
   */
  void setAstroidsVector(std::vector<glVector<float>* > collvec);

  /**
  	*@brief paints the score
  	*@param punkte points
  	*/
  void score(int punkte);

  /**
  	*@brief paints the damage
  	*@param schaden the actual damage
  	*/
  void damages(int schaden);

	/**
	 *@brief Draws the speed
	 *@param speed speed
	 */
  void Speed(float speed);

	/**
	 *@brief set Method for fighter Data like Score,damage speed
	 *@param damage actual damage
	 *@param score actual score
	 *@param speed actual speed
	 *@param shoot true when fighter shot
	 */
	void setFighterData(int damage, int score, float speed, bool shoot);

	/**
 	 *@brief renders a Spalshscreen
	 *@param breite height of the windows
	 *@param hoehe width of the windows screen
	 */
	void drawSplash(int breite, int hoehe);

	/**
	 *@brief draws radar
	 */
	 void drawRadar();

	/**
	 *@brief draws current level
	 */
	 void drawLevelEnd();

	 /**
	  *@brief sets setIncLevel
	  *@param shouldIPaint true when level accomplished
	  */
	 void setIncLevel(bool shouldIPaint);

	 /**
	  *@brief sets the Levelnumber
	  *@param levelnumber level number
	  */
	 void setLevel(int levelnumber) ;

	/**
	 *@brief sets the used painter
	 *@param paint the painter to use
	 */
	 void setPainter(QPainter *paint);

	/**
	 *@brief draws a Warning
	 */
	 void drawWarning();

	 /**
	  *@brief makes the cockpit to be visible
	  */
	 void loadCockpit();

	 /**
	  *@brief hides the cokpit
	  */
	 void deleteCockpit();

	 /**
	  *@brief return true if cockpitview
	   @return bool true if cockpitview
	  */
	 bool getView();

	 /**
	  *@brief draws the cockpit
	  */
	 void drawCockpit();

	 /**
	  * @brief draws a redscreen
	  */
	 void drawRedScreen();

	/**
	 *@brief draws the Highscore
	 */
	 void drawHighscore();

	 /**
	  * @brief draws a greenscreen
	  */
	 void drawGreenScreen();
	 /**
	  * @brief draws a GameOverscreen
	  */
	 void drawGameover(int breite, int hoehe);
private:

    QPainter *painter;
    bool     paintLevel;
    //decides if the cockpit is shown
    bool     showCockpit;
    int 	    showWarningCockpit;
    float    fighterSpeed;
    int      levelNumber;
    int      fighterDamage;
    int      fighterScore;
    //decides wether the redscreen shoul be printed
    int      ShouldIdrawRedScreen;
    int 	    ShouldIdrawGreenScreen;
    /*vector which contains the astroids in radarrange*/
    std::vector<glVector<float>* > collvec;

    // cockpit bild
    QImage cockpitImage;
    //mini raumschiff fuer radar
    QImage miniCraft;
    //image for the warning
    QImage warningPic;
    //images for color gradients fullscreen
    QImage redScreen;
    //fire animation
    QImage greenScreen;
    //Image for warning cokpit
    QImage WarningcockpitImage;
    //Image for broken cockpit
    QImage WarningcockpitBrokenImage;
    QImage cockpitBrokenImage;

    int durchmesser;
    int abstand;
    //radarmitte(breite)
    int radmidx;
    //radarmitte(hoehe)
    int radmidy;
    int breite;
    int hoehe;

};

#endif //_HUD_H
