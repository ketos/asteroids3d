/**
*   @file Partikel.cpp
*   @author gruppe3
*/
#include "rendering/partikel/Partikel.hpp"
#include <iostream>
#include "logic/Game.hpp"
#include "io/TextureManager.hpp"
#include <QtOpenGL>

Partikel::Partikel()
{

}

Partikel::~Partikel()
{
    //nothing to do
}

bool Partikel::isAlive()
{
    //get alive status
    return m_alive;
}

void Partikel::update()
{
    //Override it
}

void Partikel::renderQuad(GLuint* texture)
{
    //Calculate heading
    glVector<float> side = Game::getFighter()->getSide();
    side.normalize();
    glVector<float> up = Game::getFighter()->getUp();
    up.normalize();

    //Calculate Points for Quad
    glVector<float> vec1 = m_position + side * m_size;
    glVector<float> vec2 = m_position + up * m_size;
    glVector<float> vec3 = m_position + side * m_size + up * m_size;

    //draw particle quad
    glDisable ( GL_LIGHTING ) ;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *texture);

    //use alphatexture
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS); //starts drawing of quad
        glColor4f(m_color[0], m_color[1], m_color[2], m_alpha);
        //draw quad at this four points
        glTexCoord2f(1.0f,1.0f); glVertex3f(m_position[0], m_position[1], m_position[2]);
        glTexCoord2f(1.0f,0.0f); glVertex3f(vec1[0], vec1[1], vec1[2]);
        glTexCoord2f(0.0f,0.0f); glVertex3f(vec3[0], vec3[1], vec3[2]);
        glTexCoord2f(0.0f,1.0f); glVertex3f(vec2[0], vec2[1], vec2[2]);
    glEnd();

    glEnable ( GL_LIGHTING ) ;
} 
