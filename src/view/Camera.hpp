/**
 *  @file Camera.hpp
 *
 *  @author gruppe3
 */

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <cmath>
#include "math/Global.hpp"
#include "math/Quaternion.hpp"
#include "math/glVector.hpp"


/**
 * @brief   A small, far from perfect camera class for our viewer
 */
class Camera
{
public:

	/**
	 * @brief   Constructs a camera object
	 */
	Camera();

	/**
	 * @brief   Contructs a camera object at the given position
	 * @param x value of x
	 * @param y value of y
	 * @param z value of z
	 */
	Camera(float x, float y, float z);

	/**
	 * @brief   Deletes the camera
	 */
	virtual ~Camera() {};
    
    /**
     * @brief setzt die Kamera
     */
	void apply();
    
    /**
     * @brief Positioniert die Kamera, je nach gegebenen Koordinaten
     * 
     * @param pos   Position des Raumschiffes
     * @param front Frontvektor des Raumschiffes
     * @param up    Upvektor des Raumschiffes
     * @param side  Sidevektor des Raumschiffes
     */

    void setLocation(glVector<float> pos, glVector<float> front, glVector<float> up, glVector<float> side);
    
    /**
     * @brief Positioniert die Kamera für die Skybox
     */

	void applyRotationOnly();
    
    /**
     * @brief ändert die Entfernung der Kamera zum Raumschiff
     */    
    void zoom(float change);

    /**
     * @brief ändert die Höhe der Kamera zum Raumschiff
     */
    void changeheight(float change);
    
    /**
     * @brief Kameraänderung nach links/rechts zum Raumschiff
     */
    void changeside(float change);
    
    /**
     * @brief Setzt die DefaultKameraPosition
     */
    void setDefault();
    
    /**
     * @brief Setzt die Kamera für die Egoperspektive
     */
    void setEgo();
    
    /**
     * @brief Setzt die Kamera für die Third-Person-Perspektive
     */
    void setThird();
    
    /**
     * @brief Setzt die Kamera für die CockpitPerspektive
     */
    void setCockpit();


public:
    
    /**
     * @brief Vektor nach Oben
     */
    glVector<float> up;
    
    /**
     * @brief Vektor nach Vorne
     */
    glVector<float> front;
    
    /**
     * @brief Vektor zur Seite
     */
    glVector<float> side;
    
    /**
     * @brief Verschiebung nach oben/unten
     */
    float above;
    
    /**
     * @brief Verschiebung vorne/hinten
     */
    float behind;
    
    /**
     * @brief Verschiebung links/rechts
     */
    float beside;
};

#endif
