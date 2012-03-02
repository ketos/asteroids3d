/**
 * @file joystick-control.hpp
 *
 * @author gruppe3
 */

#ifndef __JOYSTICK_CONTROL_H__  
#define __JOYSTICK_CONTROL_H__  

#include "io/joystick.h"
#include <QTimer>

/**
 * @brief Verwaltet die Joystickeingaben
 */
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
