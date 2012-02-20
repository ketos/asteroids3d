/**
 * Transformable.h
 *
 *  @date 02.01.2012
 *  @author Thomas Wiemann
 */

#ifndef TRANSFORMABLE_H_
#define TRANSFORMABLE_H_

#include "Renderable.hpp"

#include "math/Quaternion.hpp"
#include "math/glVector.hpp"

/**
 * @brief   Base class for all objects that can be transformed, i.e.
 *          moved and rotated.
 */
class Transformable : public Renderable
{
public:
    Transformable();
    virtual ~Transformable();

    /**
     * @brief   Rotates a triangle mesh at the given axis with the given speed
     * @param axis axis to rotate
     * @param speed speed of rotation
     */
    void rotate(int axis, float speed);

    /**
     * @brief   Moves a triangle mesh at the given axis with the given speed
     * @param axis axis to move
     * @param speed speed of movement
     */
    void move(int axis, float speed);


    /**
     * @brief   Renders the object.
     */
    virtual void render() = 0;

protected:

    /**
     * @brief Computes the 4x4 transformation matrix of this object (needed for OpenGL)
     */
    void computeMatrix();

    /**
     * @brief The transformation matrix for this object
     */
    float   m_transformation[16];

    /**
     * @brief The current orientation of the x axis
     */
    glVector<float>    m_xAxis;

    /**
     * @brief The current orientation of the y axis
     */
    glVector<float>    m_yAxis;

    /**
     * @brief The current orientation of the z axis
     */
    glVector<float>    m_zAxis;


    /**
     * @brief The current position of the mesh object
     */
    glVector<float>    m_position;

    /**
     * @brief A quaternion representing the current rotation
     */
    Quaternion<float>  m_rotation;


};

#endif /* TRANSFORMABLE_H_ */
