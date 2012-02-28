#include "control/joystickcontrol.hpp"
#include "view/RenderFrame.hpp"
#include "logic/Game.hpp"
#include <iostream>

JoystickControl::JoystickControl(std::string input)
{
    joys = new Joystick();
    if(joys->init(input.c_str()) > -1) {
        std::cout << "Joystick found" << std::endl;
        connect = true;
    } else {
        std::cout << "no Joystick found" << std::endl;
        connect = false;
    }
    //m_shoot = &shoot;
}

JoystickControl::~JoystickControl()
{
    joys->stop();
    delete joys;
}

bool JoystickControl::connected()
{
    return connect;
}

void JoystickControl::update() 
{
    if(joys->getAxis(0) <-DEADZONE || joys->getAxis(0) > DEADZONE ) { // joystick links links-rechts
        float angle = joys->getAxis(0) / JOYMAX * MAX_ANGLE;        
        Game::getFighter()->rotate(YAW,  -angle);
        Game::getFighter()->rotate(ROLL, -angle);
    }
    if(joys->getAxis(1) <-DEADZONE || joys->getAxis(1) > DEADZONE ) { // joystick links up-down
        float angle = joys->getAxis(1) / JOYMAX * MAX_ANGLE;
        Game::getFighter()->rotate(PITCH,  angle);
    }
    if(joys->getAxis(2) > DEADZONE) { // schulter links
        (static_cast<Fighter*>(Game::getFighter()))->changeSpeed(SPEED);
    }
    if(joys->getAxis(5) > DEADZONE) { // schulter rechts
        (static_cast<Fighter*>(Game::getFighter()))->changeSpeed(-SPEED);
    }
    if(joys->getAxis(4) <-4*DEADZONE) { // joystick rechts up-down
        RenderFrame::m_cam.zoom(-15);
    }
    if(joys->getAxis(4) > 4*DEADZONE) {
        RenderFrame::m_cam.zoom(15);
    }
    if(joys->getAxis(3) <-4*DEADZONE) { // joystick rechts links-rechts
        RenderFrame::m_cam.changeside(-15);
    }
    if(joys->getAxis(3) > 4*DEADZONE) {
        RenderFrame::m_cam.changeside(15);
    }
    if(joys->getButton(0) > 0) { //A
        if(RenderFrame::shoot) {
            (static_cast<Fighter*>(Game::getFighter()))->shoot();
            RenderFrame::shoot = false;
        }
    }
//    if(joys->getButton(1) > 0) { //B
//    }
    if(joys->getButton(2) > 0) { //X
        RenderFrame::m_cam.setEgo();
    }
    if(joys->getButton(3) > 0) { //Y
        RenderFrame::m_cam.setThird();
    }
    if(joys->getButton(4) > 0) { //LB
        RenderFrame::m_cam.changeheight(5);
    }
    if(joys->getButton(5) > 0) { //RB
        RenderFrame::m_cam.changeheight(-5);
    }/*
    if(joys->getButton(6) > 0) { //Back
    }
    if(joys->getButton(7) > 0) { //Start
    }
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
