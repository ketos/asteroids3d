/**
 * @file joystick-control.hpp
 */

#ifndef __JOYSTICK_CONTROL_H__  
#define __JOYSTICK_CONTROL_H__  

#include "io/joystick.h"
#include <QTimer>

/**
 * @brief einige Konstanten
 */
#define DEADZONE 5000.0
#define JOYMAX 32767.0
#define MAX_ANGLE 0.05
#define SPEED 1


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
