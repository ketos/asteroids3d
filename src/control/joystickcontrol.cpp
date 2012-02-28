#include "control/joystickcontrol.hpp"
#include "logic/Game.hpp"
#include <iostream>

JoystickControl::JoystickControl(std::string input, Fighter &mesh, Camera &cam, bool &shoot) : m_mesh(mesh), m_cam(cam)
{
    
    if(joys->init(input.c_str()) > -1) {
        std::cout << "Joystick found" << std::endl;
        connect = true;
    } else {
        std::cout << "no Joystick found" << std::endl;
        connect = false;
    }
    m_shoot = &shoot;
}

JoystickControl::~JoystickControl()
{
    joys->stop();
}

bool JoystickControl::connected()
{
    return connect;
}

void JoystickControl::update() {
    if(joys->getAxis(0) <-DEADZONE || joys->getAxis(0) > DEADZONE ) { // joystick links links-rechts
        float angle = joys->getAxis(0) / JOYMAX * MAX_ANGLE;        
        m_mesh.rotate(YAW,  -angle);
    }
    if(joys->getAxis(1) <-DEADZONE || joys->getAxis(1) > DEADZONE ) { // joystick links up-down
        float angle = joys->getAxis(1) / JOYMAX * MAX_ANGLE;
        m_mesh.rotate(PITCH,  angle);
    }
    if(joys->getAxis(2) > DEADZONE) { // schulter links
        std::cout << joys->getAxis(2) << std::endl;
        m_mesh.changeSpeed(10);
    }
    if(joys->getAxis(5) > DEADZONE) { // schulter rechts
        std::cout << joys->getAxis(2) << std::endl;
        m_mesh.changeSpeed(-10);
    }
    if(joys->getAxis(4) <-4*DEADZONE) { // joystick rechts up-down
        m_cam.zoom(-15);
    }
    if(joys->getAxis(4) > 4*DEADZONE) {
        m_cam.zoom(15);
    }
    if(joys->getButton(0) > 0) { //A
        if(m_shoot) {
            m_mesh.shoot();
            m_shoot = false;
            //RenderFrame::m_timer2->start();
        }
    }/*
    if(joys->getButton(1) > 0) { //B
    }
    if(joys->getButton(2) > 0) { //X
    }
    if(joys->getButton(3) > 0) { //Y
    }*/
    if(joys->getButton(4) > 0) { //LB
        m_cam.changeheight(5);
    }
    if(joys->getButton(5) > 0) { //RB
        m_cam.changeheight(-5);
    }
    if(joys->getButton(6) > 0) { //Back
        if(m_shoot) {
            m_shoot = false;
            //aenderModel("arrow.3ds");
            //RenderFrame::m_timer2->start();
        }  
    }
    if(joys->getButton(7) > 0) { //Start
        if(m_shoot) {
            m_shoot = false;
            //aenderModel("bearcat.3ds");
            //RenderFrame::m_timer2->start();
        }    
    }/*
    if(joys->getButton(8) > 0) { //BIG
    }
    if(joys->getButton(9) > 0) { //AxisLeft
    }
    if(joys->getButton(10) > 0) {//AxisRight
    }
    if(joys->getButton(11) > 0) {//DpadRight
    }
    if(joys->getButton(12) > 0) {//DpadUp
    }
    if(joys->getButton(13) > 0) {//DpadLeft
    }
    if(joys->getButton(14) > 0) {//DpadDown
    }
    if(joys->getButton(15) > 0) {//None
    }*/
}


