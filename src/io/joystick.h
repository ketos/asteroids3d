/*   Copyright (C) 2009  Nathaniel <linux.robotdude@gmail.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

 #ifndef __JOYSTICK_H__
 #define __JOYSTICK_H__ 1

#include <linux/joystick.h>

#ifdef __cplusplus              /* If the language is C++, use the Joystick class */

class Joystick {
protected:
    char *device;               /* Holds the path to the device file */
    int js_fd;                  /* Holds the joystick file descriptor */
    int axis_count;             /* Holds the number of axes the joystick has */
    int button_count;           /* Holds the number of buttons the joystick has */
    char name[80];              /* Holds the name of the joystick */
    int *axes;                  /* A pointer to the values of the axes of the joystick */
    char *buttons;              /* A pointer to the values of the buttons of the joystick */
    struct js_event event;      /* The joystick event structure */
public:
    Joystick();                 /** @brief A constructor that does nothing, open must then be called before any other function int the class */
    Joystick( const char* joydev ); /** @brief The constructor for the object, must have the joystick port */
    int init( const char* joydev ); /** @brief Opens a joystick following a blank constructor or after a close */
    void stop();                /** @brief A function that calls the deconstructor to close an open joystick */
    char getButton( int button ); /** @brief Returns the value of the specified button */
    int getAxis( int axis );    /** @brief Returns the value of the specified axis */
    char* getName();            /** @brief Returns the name of the name of the joystick */
    char* getDevice();          /** @brief Returns the path of the device file the joystick is attached to */
    int numAxes();              /** @brief Returns the number of axes the joystick has */
    int numButtons();           /** @brief Returns the number of buttons the joystick has */
    int connected;              /* Holds status of the connection state to the joystick */
};

#else                           /* If the language is C, use the c implementation */

typedef struct {                /* A Structure to house the variable required in maintaining a joystick */
    char *device;               /* Holds the path to the device file */
    int js_fd;                  /* Holds the joystick file descriptor */
    int axis_count;             /* Holds the number of axes the joystick has */
    int button_count;           /* Holds the number of buttons the joystick has */
    char name[80];              /* Holds the name of the joystick */
    int *axes;                  /* A pointer to the values of the axes of the joystick */
    char *buttons;              /* A pointer to the values of the buttons of the joystick */
    struct js_event event;      /* The joystick event structure */
} Joystick ;

Joystick* js_open ( const char* joydev );      /** @brief Function to open the joystick from a device file */

char getJSButton( Joystick* js, int button );  /** @brief Returns the value of a button of the joystick */

int getJSAxis( Joystick* js, int axis );       /** @brief Returns the value of an axis of the joystick */

void js_close( Joystick* js );                 /** @brief Closes a joystick instance */

#endif

#endif
