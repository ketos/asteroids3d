/**
 * @file joystickcontrol.hpp
 *
 * @author gruppe3
 */

#ifndef __JOYSTICK_CONTROL_H__  
#define __JOYSTICK_CONTROL_H__  

#include "io/joystick.h"
#include <QTimer>

/**
 * @brief Verwaltet die Joystickeingaben
 *          Aktuell angepasst an den Wireless XBox360 Controller
 */
class JoystickControl
{
public:
    /**
     * @brief Startet den Joystick, wenn einer vorhanden
     *
     * @param input Ort des Joysticks (Ubuntu "/dev/input/js0")
     */
    JoystickControl(std::string input);

    /**
     * @brief Destruktor
     */
    ~JoystickControl();

    /**
     * @brief gibt zurück ob ein Joystick verbunden wurde
     * 
     * @return ob einer verbunden ist
     */
    bool connected();
    /**
     * @brief Fragt die Achsen und Buttons des Joysticks ab
     */
    void update();

private:
    /**
     * @brief Der Joystick
     */
    Joystick* joys;
    /**
     * @brief Verbunden oder nicht
     */
    bool connect;
};

#endif
