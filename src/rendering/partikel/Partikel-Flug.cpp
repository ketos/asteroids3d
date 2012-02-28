#include "rendering/partikel/Partikel-Flug.hpp"
#include <QtOpenGL>


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

    GLUquadricObj* qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    glNewList(3, GL_COMPILE);
    gluSphere( qobj, 100, 20, 20);
    glEndList();
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
}
