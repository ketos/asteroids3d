/**
 * @file Asteorid.hpp
 * @author gruppe3
 */

#ifndef ASTEROID_HPP_
#define ASTEROID_HPP_

#include <GL/glu.h>
#include <GL/glut.h>
#include <QThread>
#include <QObject>
#include <QMetaType>
#include <stdio.h>

#include "io/SoundManager.hpp"
#include "TexturedMesh.hpp"

// We use common cpp threads for this class:
// http://www.gnutelephony.org/index.php/GNU_Common_C%2B%2B

/**
 * @brief Asteorid
 */
class Asteorid: public QThread, public TexturedMesh
{
Q_OBJECT

public:

    /**
     * @brief Contructor. Build a Asteorid on the position. The Asteorid will move on given axis.
     * @param   start_position   Position of this Asteorid
     * @param   flight_axis   Axis the Asteorid will move on
     */
    Asteorid(glVector<float> start_position, glVector<float> flight_axis);

    /**
     * @brief Moves the Asteorid until it's over.
     */
	void run();

    /**
      * @brief returns position
      */
	glVector<float> getPosition();

    /**
     * @brief Returns the status of this Asteorid.
     * @return false, if the Asteorid's lifetime is over and true otherwise
     */
	bool isAlive();

    /**
     * @brief destroys the asteorid
     */
	void destroy();

    /**
     * @brief changes the flight-direction of the Astroid
	 * @param dir New Axis
     */
     void changeDirection(glVector<float> dir);

    /**
     * @brief returns the flight-axis
     */
     glVector<float> getFlightAxis();
     /**
     * @brief Sets new Flight Axis
	 * @param new_axis New Direction of Asteorid
     */
     void set_flight_axis(glVector<float> new_axis);
    /**
     * @brief returns the Radius of the Asteorid
     * @return float Radius
     */
     float get_radius();
    /**
     * @brief returns true, if this Asteorid is a little one
	 * @return bool true, if this Asteorid is a little one
     */
     bool is_mini();
    /**
     * @brief returns if this Asteorid is hittable
     */
     bool is_hitable();
    /**
     * @brief Sets the Hittability of the Asteorid
	 * @param hit Boolean to set the Hitability
     */
     void set_hitable(bool hit);
    /**
     * @brief Sets the Speed of the Asteorid
	 * @param s Speed of the Asteorid
     */
     void set_speed(float s);

protected:
   	/**
     * @brief Status of Asteorid
     */
	bool alive;
  	/**
     * @brief Flight Axis of Asteorid
     */
	glVector<float> flight_axis;
    /**
     * @brief Speed of Asteorid
     */
	float speed;
    /**
     * @brief Radius of Asteorid
     */
	float radius;
    /**
     * @brief Boolean, if Asteorid is a little one
     */
	bool mini;
    /**
     * @brief Boolean, if Asteorid is hittable right now
     */
	bool hitable;
    /**
     * @brief wait
     */
	int wait;

signals:
    /**
     * @brief Signal with Position Informations
	 * @param x x-Position
	 * @param y y-Position
	 * @param z z-Position
     */
	void destroyed(float x, float y, float z);
	/**
	 * @brief Signal with no Informations
	 */
	void hit();
};

#endif /* ASTEORID_HPP_ */
