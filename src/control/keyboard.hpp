/**
 * @brief keyboard.hpp
 */
    
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <QKeyEvent>
#include <set>

#define ANGLE 0.05
#define SPEED 1

class Keyboard
{
public:
    static void Init();
	static void keypressed(QKeyEvent* e);
	static void keyrelease(QKeyEvent* e);
    static void update();
protected:
    static std::set<int> m_pressedKeys;
    static bool m_shoot;
};

#endif
