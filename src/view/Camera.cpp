/**
 * Camera.cpp
 *
 *  @date 27.11.2011
 *  @author Thomas Wiemann
 */

#include "Camera.hpp"

#include <GL/gl.h>      /* Header File For The OpenGL32 Library */
#include <GL/glu.h>     /* Header File For The GLu32 Library */

Camera::Camera()
{
    above = 300;
    behind= 1500;
}

void Camera::applyRotationOnly()
{
    glLoadIdentity();
    gluLookAt(front.x, front.y, front.z, 0, 0, 0, up.x, up.y, up.z);
}

void Camera::setLocation(glVector<float> pos, glVector<float> front1, glVector<float> up1) {
        
    // Clear matrix stack  
    glLoadIdentity();
    
    front = (front1);
    front.normalize();
    up = (up1);
    up.normalize();
    
    glVector<float> cam = pos + up * above + front * behind;
    pos = pos + up * above;
    
    // Calc transformation Matrixwf
    gluLookAt(cam.x, cam.y, cam.z,
              pos.x, pos.y, pos.z,
              up.x , up.y , up.z);
    
}

void Camera::zoom(float change) 
{
    behind += change;
}

void Camera::changeheight(float change)
{
    above += change;
}   

void Camera::apply()
{
    // Clear matrix stack
    glLoadIdentity();

    // Calc transformation matrix
    gluLookAt(0, 0, 0,
              0, 0, 1,
              0.0, 1.0, 0.0);
}
