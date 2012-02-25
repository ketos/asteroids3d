/**
 * @file joystick-control.hpp
 */

#ifndef __JOYSTICK_CONTROL_H__  
#define __JOYSTICK_CONTROL_H__  

#include "io/joystick.h"
#include <QTimer>

#include "view/Camera.hpp"
#include "rendering/Fighter.hpp"

/**
 * @brief einige Konstanten
 */
#define DEADZONE 8000
#define JOYMAX 32000
#define MAX_ANGLE 0.05
#define SPEED 1


class JoystickControl
{
public:
    JoystickControl(std::string input, Fighter &mesh, Camera &cam, bool &shoot);
    ~JoystickControl();
    bool connected();
    void update();

private:
    Joystick* joys;
    bool connect;
    Fighter m_mesh;
    Camera m_cam;
    bool m_shoot;
};

#endif
