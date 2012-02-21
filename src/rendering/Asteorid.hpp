/**
 * @file
 * Asteorid.hpp
 *
 */

#ifndef ASTEROID_HPP_
#define ASTEROID_HPP_

#include "TexturedMesh.hpp"
// We use common cpp threads for this class: 
// http://www.gnutelephony.org/index.php/GNU_Common_C%2B%2B 
#include <GL/glu.h>
#include <GL/glut.h>
#include <QThread>


/**
 * @brief Renders a Asteorid
 */
class Asteorid: public TexturedMesh, public QThread
{

public:

    /**
     * @brief Contructor. Build a Asteorid on the given Fighter's
     *                      position. The Asteorid will move on the
     *                      given axis.
     * @param   start_position   Position of the fighter that shoots this Asteorid
     * @param   flight_axis   Axis the Asteorid will move on
     */
    Asteorid(glVector<float> start_position, glVector<float> flight_axis);

    /**
     * @brief Moves the Asteorid until it's lifetime is over.
     */
	void run();
    
    

    /**
     * @brief Returns the status of this Asteorid.
     * @return false, if the Asteorid's lifetime is over and true otherwise
     */
	bool isAlive();
	
    /**
     * @brief destroys the asteorid
     */
	void destroy();

private:
    // true, if the Asteorid's lifetime isn't over yet
	bool alive;
    // axis, the Asteorid is moving on (one of the shooting fighter's axes)
	glVector<float> flight_axis;
};


#endif /* BULLET_HPP_ */
