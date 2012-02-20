/**
 * glNormal.cpp
 *
 *  @date 02.01.2012
 *  @author Thomas Wiemann
 */

#include "glNormal.hpp"

template<typename T>
glNormal<T>::glNormal(const glVector<T> &v)
    : glVector<T>(v)
{
    normalize();
}

template<typename T>
glNormal<T>::glNormal(T x, T y, T z)
    : glVector<T>(x, y, z)
{
    normalize();
}


template<typename T>
glNormal<T>::~glNormal()
{
    // TODO Auto-generated destructor stub
}

template<typename T>
void glNormal<T>::normalize()
{
    // Normalize the vector
    T mag2 = this->x * this->x + this->y * this->y + this->z * this->z;
    if (fabs(mag2 - 1.0f) > TOLERANCE)
    {
        T mag = sqrt(mag2);
        this->x /= mag;
        this->y /= mag;
        this->z /= mag;
    }
}

