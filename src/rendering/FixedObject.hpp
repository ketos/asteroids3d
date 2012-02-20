
/**
 * FixedObject.h
 *
 *  @date 02.01.2012
 *  @author Thomas Wiemann
 */

#ifndef FIXEDOBJECT_H_
#define FIXEDOBJECT_H_

#include "Renderable.hpp"

/**
 * @brief   Interface stub to mark object that cannot be moved.
 */
class FixedObject : public Renderable
{
public:
    FixedObject() {}

};

#endif /* FIXEDOBJECT_H_ */
