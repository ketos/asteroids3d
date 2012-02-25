/**
 * @brief keyboard.hpp
 */
    
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "view/Camera.hpp"
#include "rendering/Fighter.hpp"
#include <QKeyEvent>
#include <set>

#define ANGLE 0.05
#define SPEED 1

class Keyboard
{
public:
    Keyboard(Fighter &mesh, Camera &cam, bool &shoot);
    ~Keyboard();
    void keypressed(QKeyEvent *event);
    void keyrelease(QKeyEvent *event);
    void update();
protected:
    std::set<int>* m_pressedKeys;
    Fighter m_mesh;
    Camera m_cam;
    bool m_shoot;
};

#endif
