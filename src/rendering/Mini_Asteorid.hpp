/**
 * @file Mini_Asteorid.hpp
 * @author gruppe3
 */

#ifndef MINI_ASTEROID_HPP_
#define MINI_ASTEROID_HPP_

#include "TexturedMesh.hpp"
#include "Asteorid.hpp"

// We use common cpp threads for this class: 
// http://www.gnutelephony.org/index.php/GNU_Common_C%2B%2B 
#include <GL/glu.h>
#include <GL/glut.h>
#include <QThread>


/**
 * @brief Mini_Asteorid
 */
class Mini_Asteorid: public Asteorid
{
public:
	/**
	 * @brief Constructs a little Asteorid
	 */
    Mini_Asteorid(glVector<float> start_position, glVector<float> flight_axis);
	/**
	 * @brief Runs the Thread
	 */
	void run();
    
};


#endif /* MINI_ASTEORID_HPP_ */
