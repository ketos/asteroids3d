#include "rendering/partikel/Partikel-Flug.hpp"
#include <QtOpenGL>
#include <iostream>
#include "logic/Game.hpp"
#include "io/tga.h"

//Static Texture-Member
GLuint PartikelFlug::TexID1 = 0;

PartikelFlug::PartikelFlug(float lifetime, glVector<float> pos, float size, glVector<float> color)
{
    m_lifetime = lifetime;
    m_position = pos;
    m_size     = size;
    m_color    = color;
    m_alive = true;

    //Load texture one time
    if(!TexID1)
    {
        TexID1 = LoadTexture("res/images/Logo.tga");
    }
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
    glVector<float> side = Game::getFighter()->getSide();
    side.normalize();
    glVector<float> up = Game::getFighter()->getUp();
    up.normalize();

    glVector<float> vec1 = m_position + side * 30;
    glVector<float> vec2 = m_position + up * 30;
    glVector<float> vec3 = m_position + side *30 + up * 30;


    glEnable ( GL_RGBA_MODE ) ;
    glDisable ( GL_LIGHTING ) ;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,TexID1);

    glEnable (GL_BLEND); 
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS); //starts drawing of points
        //glColor3f(0.0f,0.0f,0.0f);

        glTexCoord2f(1.0f,1.0f); glVertex3f(m_position[0], m_position[1], m_position[2]);
        glTexCoord2f(1.0f,0.0f); glVertex3f(vec1[0], vec1[1], vec1[2]);
        glTexCoord2f(0.0f,0.0f); glVertex3f(vec3[0], vec3[1], vec3[2]);
        glTexCoord2f(0.0f,1.0f); glVertex3f(vec2[0], vec2[1], vec2[2]);
        //glVertex3f(0,0,0);
    glEnd();//end drawing of points
    glEnable ( GL_LIGHTING ) ;
    glDisable ( GL_RGBA_MODE ) ;
}

GLuint PartikelFlug::LoadTexture(char *TexName)
{
   TGAImg Img;        // Image loader
   GLuint Texture;
 
  // Load our Texture
   if(Img.Load(TexName)!=IMG_OK)
    return -1;
 
   glGenTextures(1,&Texture);            // Allocate space for texture
   glBindTexture(GL_TEXTURE_2D,Texture); // Set our Tex handle as current
 
   // Create the texture
    if(Img.GetBPP()==24)
     glTexImage2D(GL_TEXTURE_2D,0,3,Img.GetWidth(),Img.GetHeight(),0,
                  GL_RGB,GL_UNSIGNED_BYTE,Img.GetImg());
    else if(Img.GetBPP()==32)
     glTexImage2D(GL_TEXTURE_2D,0,4,Img.GetWidth(),Img.GetHeight(),0,
                  GL_RGBA,GL_UNSIGNED_BYTE,Img.GetImg());
    else
     return -1;
 
   // Specify filtering and edge actions
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
 
   return Texture;
}
