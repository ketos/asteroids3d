/**
 *  @file Quaternion.hpp
 *
 *  @date 05.12.2011
 *  @author Thomas Wiemann
 */

#ifndef __QUATERNION_HPP__
#define __QUATERNION_HPP__

#include "Global.hpp"
#include "glVector.hpp"

#include <iostream>
#include <cmath>

/**
 * @brief   Quaternion representation for OpenGL. Based on: 
 *          http://gpwiki.org/index.php/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation
 *
 */

template<typename T>
class Quaternion {

public:

	/**
	 * @brief   Construcs a default quaternion object
	 */
	Quaternion();

	/**
	 * @brief   Destructor
	 */
	~Quaternion();

	/**
	 * @brief   Construcs (with fromAxis()) a quaternion with a given glVector and an angle
	 * @param vec vector
	 * @param angle angle
	 */
	Quaternion(glVector<T> vec, T angle);

	/**
	 * @brief   Constructs a quaternion with three given values and an angle
	 * @param x x-value
	 * @param y y-value
	 * @param z z-value
	 * @param w angle
	 */
	Quaternion(T x, T y, T z, T w);

	/**
	 * @brief   Constructs a quaternion with a given T-pointer and an angle
	 * @param vec vector(pointer)
	 * @param w angle
	 */
	Quaternion(T* vec, T w);
  
	/**
	 * @brief   Calculates a quaternion with a given vector and an angle
	 * @param axis vector
	 * @param angle angle
	 */
	void fromAxis(glVector<T> axis, T angle);
 
	/**
	 * @brief   Conjugates a quaternion
	 * @return quaternion (conjugate)
	 */
	Quaternion getConjugate();

	/**
	 * @brief   Defines the quaternion-quaternion multiplication
	 * @param rq quaternion
	 * @return quaternion
	 */
	Quaternion operator* (Quaternion rq);

	/**
	 * @brief   Defines the vector-quaternion multiplication
	 * @param vec vector
	 * @return vector
	 */
	glVector<T> operator* (glVector<T> vec);
  
private:

	/**
	 * @brief   Value of angle, x, y and z
	 */
	T w, x, y, z;
};

#include "Quaternion.tcc"

#endif

