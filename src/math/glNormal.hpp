/**
 * glNormal.h
 *
 *  @date 02.01.2012
 *  @author Thomas Wiemann
 */

#ifndef GLNORMAL_H_
#define GLNORMAL_H_

#include "glVector.hpp"

/**
 * @brief enthält einen Vektor mit der Länge 1
 */

template<typename T>
class glNormal : public glVector<T>
{
public:

    glNormal(const glVector<T> &v );
    glNormal(T x, T y, T z);

    virtual ~glNormal();

private:
    /**
     * @brief   Normalize a glVector
     */
    void normalize();
};

#include "glNormal.tcc"

#endif /* GLNORMAL_H_ */
