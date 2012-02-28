#include "rendering/partikel/Partikel-Flug.hpp"
#include <QtOpenGL>
#include <iostream>

PartikelFlug::PartikelFlug(float lifetime,
                       glVector<float> pos,
                       float size, 
                       glVector<float> color)
{
    m_lifetime = lifetime;
    m_position = pos;
    m_size     = size;
    m_color    = color;
    m_alive = true;

//    glNewList(3, GL_COMPILE);
//    
//    gluSphere( qobj3, 100, 20, 20);
//    glEndList();
}

PartikelFlug::~PartikelFlug()
{

}

bool PartikelFlug::isAlive()
{
    return m_alive;
}

void PartikelFlug::update()
{
    m_lifetime--;
    if(m_lifetime == 0)
    {
        m_alive = false;
    }
}

void PartikelFlug::render()
{    
  }/*  
    GLUquadricObj* q = gluNewQuadric();
    gluQuadricDrawStyle(q, GLU_FILL);
    computeMatrix();
    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D, Kugeltextur[0]);
    //glTranslatef(0.0f, 0.0f, 0.0f);  //Kugel in die Mitte verschieben

    gluSphere(q, 100, 32, 16);
    glPopMatrix();    
}
/*
    glPointSize(4.0);
    glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_POINTS);
        glVertex3f(m_position[0], m_position[1], m_position[2]);
    glEnd;
    glDisable(GL_BLEND);
    glDisable(GL_POINT_SMOOTH);
}*/
/*    
    std::cout << "Partikel Render" << std::endl;
    // Compute transformation matrix
	computeMatrix();
    // Push old transformation of the OpenGL matrix stack and
	// start rendering the bullet in according to the
	// internal transformation matrix
	glPushMatrix();
	glMultMatrixf(m_transformation);
    
    glCallList(3);
    
    //glutSolidTeapot(50);
	//glutSolidSphere(10,16,16);
	// Pop transformation matrix of this object
	// to restore the previous state of the OpenGL
	// matrix stack
	glPopMatrix();
}*/
