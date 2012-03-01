/**
 * @file joystick-control.hpp
 */

#ifndef __JOYSTICK_CONTROL_H__  
#define __JOYSTICK_CONTROL_H__  

#include "io/joystick.h"
#include <QTimer>

class JoystickControl
{
public:
    JoystickControl(std::string input);
    ~JoystickControl();
    bool connected();
    void update();

private:
    Joystick* joys;
    bool connect;
};

#endif
