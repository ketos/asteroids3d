/**
 *  @file Camera.hpp
 *
 *  @date 27.11.2011
 *  @author Thomas Wiemann
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
	 * @brief   Moves the camera left by m_speed units
	 */
	void moveLeft();

	/**
	 * @brief   Moves the camera right by m_speed units
	 */
	void moveRight();

	/**
	 * @brief   Moves the camera up by m_speed units
	 */
	void moveUp();

	/**
	 * @brief   Moves the camera down by m_speed units
	 */
	void moveDown();

	/**
	 * @brief   Moves the camera forward by m_speed units
	 */
	void moveForward();

	/**
	 * @brief   Moves the camera backwards by m_speed units
	 */
	void moveBackward();

	/**
	 * @brief   Turns left by m_rotSpeed units
	 */
	void turnLeft();

	/**
	 * @brief   Turns right by m_rotSpeed units
	 */
	void turnRight();

	/**
	 * @brief   Turns up by m_rotSpeed units
	 */
	void turnUp();

	/**
	 * @brief   Turns down by m_rotSpeed units
	 */
	void turnDown();

    void rotateLeft();
    void rotateRight();

	/**
	 * @brief   Sets the current movement speed
	 * @param speed Movement speed
	 */
	void setSpeed(float _speed){m_speed = _speed;};

	/**
	 * @brief   Sets the current turn speed
	 * @param speed turn speed
	 */
	void setTurnSpeed(float _speed) {m_turnSpeed = _speed;};

	/**
	 * @brief   Increases the the current speed by \ref addSpeed units
	 * @param addSpeed Units to increase
	 */
	void incSpeed(float addSpeed){m_speed += addSpeed;};

	/**
	 * @brief   Increases the the current turn speed by \ref decSpeed units
	 * @param decSpeed Units to increase
	 */
	void incTurnSpeed(float decSpeed){m_turnSpeed += decSpeed;};

	/**
	 * @brief   Applies the current camera transformation to the OpenGL
	 *          matrix stack
	 */
	void apply();

    void setLocation(glVector<float> pos, glVector<float> lookat);

	void applyRotationOnly();

public:

	///The current orientation of the x-axis
	glVector<float> m_baseX;

	///The current orientation of the y-axis
	glVector<float> m_baseY;

	///The current orientation of the z-axis
	glVector<float> m_baseZ;

	/**
	 * @brief The current speed
	 */
	float m_speed;

	/**
	 * @brief The current turn speed
	 */
	float m_turnSpeed;

	/**
	 * @brief The current rotation around the y-Axis
	 */
	float m_rotY;

	/**
	 * @brief The current rotation around the x-Axis
	 */
	float m_rotX;

	/**
	 * @brief The current rotation around the z-Axis
	 */
	float m_rotZ;

	/**
	 * @brief The current x position
	 */
	float m_px;

	/**
	 * @brief The current y position
	 */
	float m_py;

	/**
	 * @brief The current z position
	 */
	float m_pz;

	/**
	 * @brief The initial x position
	 */
	float m_ix;

	/**
	 * @brief The initial y position
	 */
	float m_iy;

	/**
	 * @brief The initial z position
	 */
	float m_iz;

	/**
	 * @brief The x component of the "look at" vector
	 */
	float m_lx;

	/**
	 * @brief The y component of the "look at" vector
	 */
	float m_ly;

	/**
	 * @brief The z component of the "look at" vector
	 */
	float m_lz;
};

#endif
