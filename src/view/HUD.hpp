#ifndef _HUD_H
#define _HUD_H

#include <QBrush>
#include <QFont>
#include <QImage>
#include <QPen>
#include <QGLWidget>
#include <QString>
#include <string.h>
#include <QFontMetrics>
#include <vector>
#include <sstream>
#include <string>
#include <iostream> 
#include <QPushButton>

#include "math/glVector.hpp"

class HUD
{
public:
  /**
  	*@brief Defualt Constructor
  	*/
  	HUD();
  /**
  	*@brief Destructor
  	*/
    ~HUD();
  /**
   * @brief Draws the HUD
   * @param painter Used QPainter
   * @param x width of the window;
   * @param y hiegth of the window;
   * @param f Used Font
   */
  void draw(int x ,int y, QFont f);
    
  /**
   *@brief Draws the given Astroid on the rada
   *@param painter used QPainter
   *@param radarraange the max distance for astroids
   *@param durchmesser diameter of the radar
   *@param radarmidx x value of the radarmid
   *@param radarmidy y value of the radarmid
   *@param QPainter used QPainter
   */
  void drawRadarAstroid(glVector<float>* vec, float radarrange, int durchmesser, int radarmidx, int radarmidy);

  /**
   *@brief sets the collvec which contains the astroids in Radarrange
   *@param vector vector with astroids in radarrange
   */
  void setAstroidsVector(std::vector<glVector<float>* > collvec);

  /**
  	*@brief paint the score
  	*@param points
  	*@param breite width
  	*@param used Qpainter
  	*/
  void score(int punkte, int breite);

  /**
  	*@brief paint the damage
  	*@param damage the actual damage
  	*@param breite width
  	*@param used Qpainter
  	*/
  void damages(int schaden);
	
	/**
	 *@brief Draws the speed
	 *@param int speed 
	 *@param breite width
	 *@param painter used Painter
	 */  
  void Speed(float speed);
  
	/**
	 *@briefset Method for fighter Data like Score,damage speed
	 *@param damage actual damage
	 *@param score actual score
	 *@param speed actual speed
	 */
	void setFighterData(int damage, int score, float speed, bool shoot); 
	
	/**
 	 *@brief renders a Spalshscreen
	 *@param int breite width of the screen
	 *@param int hoehe higth of the screen
	 *@param painter used qpainter 
	 */   
	void drawSplash(int breite, int hoehe);
	/**
	 *@brief draws radar
	 *@param breite height of the windows
	 *@param hoehe width of the windows
	 */
	 void drawRadar(int width, int height);
	 
	/**
	 *@brief draws current level
	 *@param breite height of the windows
	 *@param hoehe width of the windows
	 *@param actLevel actual level
	 */
	 void drawLevelEnd();
	 
	 void setIncLevel(bool shouldIPaint);
	 
	 void setLevel(int levelnumber) ;
	
	 void setPainter(QPainter *paint);
	/**
	 *@draws a Warning
	 */
	 void drawWarning();	 
	 /*
	  *@brief makes the cockpit to be visible
	  */
	 void loadCockpit();
	 /*
	  *@brief hides the cokpit
	  */
	 void deleteCockpit();
	 /*
	  *@brief return true if cockpitview
	   @return  true if cockpitview
	  */
	 bool getView();
	 /*
	  *@brief draws the cockpit 
	  */
	 void drawCockpit();	
	 /*
	  * @brief draws a redscreen
	  */
	  void drawRedScreen();
	 /*
	  * @brief draws a greenscreen
	  */
	  void drawGreenScreen();
private:
    //HUD(const HUD&);
    //~HUD();
    //static HUD* instance;
    /*used QPainter*/

    QPainter *painter;
    bool     paintLevel;
    //decides if the cockpit is shown
    bool     showCockpit;
    int 	 showWarningCockpit;
    float    fighterSpeed;
    int      levelNumber;
    int      fighterDamage;
    int      fighterScore;
    //decides wether the redscreen shoul be printed 
    int      ShouldIdrawRedScreen;
    int 	 ShouldIdrawGreenScreen;
    /*vector which contains the astroids in radarrange*/
    std::vector<glVector<float>* > collvec;
    // cockpit bild 
    QImage *cockpitImage;
    //mini raumschiff fuer radar
    QImage miniCraft;
    //image for the warning
    QImage warningPic;
    //images for color gradients fullscreen
    QImage redScreen;
    QImage greenScreen;
    //Image for warning cokpit
    QImage WarningcockpitImage;
 	int durchmesser;
	int abstand;     
   int radmidx;
   int radmidy;
   int breite;
   int hoehe; 
};

#endif //_HUD_H
