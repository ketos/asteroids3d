/**
 * Skybox.cpp
 *
 *  @date 11.12.2011
 *  @author Thomas Wiemann
 */

#include "Skybox.hpp"
#include "io/TextureFactory.hpp"
#include "view/MainWindow.hpp"

Skybox::Skybox(int width, string files[6], Camera &cam)
    : m_width(width), m_cam(cam)
{

    // Create textures
    m_textures = new Texture*[6];
    for(int i = 0; i < 6; i++)
    {
        m_textures[i] = TextureFactory::instance().getTexture(files[i]);
    }

}

Skybox::~Skybox()
{
	// Delete textures
	for(int i = 0; i < 6; i++)
	{
		delete m_textures[i];
	}
	delete[] m_textures;
}

void Skybox::render()
{
    // Enable/Disable features

    glPushMatrix();
    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);

    m_cam.applyRotationOnly();

    // Set color
    glColor3f(1.0f, 1.0f, 1.0f);

    float pos = 0.5f * m_width;

    // Render right quad
    if(m_textures[3])
    {
        m_textures[3]->bind();
        glBegin(GL_QUADS);
        glTexCoord2f(1, 1); glVertex3f(  pos, -pos,  pos );
        glTexCoord2f(1, 0); glVertex3f(  pos, -pos, -pos );
        glTexCoord2f(0, 0); glVertex3f(  pos,  pos, -pos );
        glTexCoord2f(0, 1); glVertex3f(  pos,  pos,  pos );
        glEnd();
    }

    // Render rear quad
    if(m_textures[0]) // Replace code here -> wrong quad!!!
    {
        m_textures[0]->bind();
        glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f(  -pos, -pos, -pos );
        glTexCoord2f(1, 1); glVertex3f(   pos, -pos, -pos );
        glTexCoord2f(1, 0); glVertex3f(   pos,  pos, -pos );
        glTexCoord2f(0, 0); glVertex3f(  -pos,  pos, -pos );
        glEnd();
    }

    // Render the front quad
    if(m_textures[2])
    {
        m_textures[2]->bind();
        glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f( -pos, -pos,  pos );
        glTexCoord2f(1, 1); glVertex3f(  pos, -pos,  pos );
        glTexCoord2f(1, 0); glVertex3f(  pos,  pos,  pos );
        glTexCoord2f(0, 0); glVertex3f( -pos,  pos,  pos );
        glEnd();
    }

    // Render the left quad
    if(m_textures[1])
    {
        m_textures[1]->bind();
        glBegin(GL_QUADS);
        glTexCoord2f(1, 1); glVertex3f( -pos, -pos, -pos );
        glTexCoord2f(0, 1); glVertex3f( -pos, -pos,  pos );
        glTexCoord2f(0, 0); glVertex3f( -pos,  pos,  pos );
        glTexCoord2f(1, 0); glVertex3f( -pos,  pos, -pos );
        glEnd();
    }

    // Render the top quad
    if(m_textures[4])
    {
        m_textures[4]->bind();
        glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f( -pos,  pos, -pos );
        glTexCoord2f(0, 0); glVertex3f( -pos,  pos,  pos );
        glTexCoord2f(1, 0); glVertex3f(  pos,  pos,  pos );
        glTexCoord2f(1, 1); glVertex3f(  pos,  pos, -pos );
        glEnd();
    }

    // Render the bottom quad
    if(m_textures[5])
    {
        m_textures[5]->bind();
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -pos, -pos, -pos );
        glTexCoord2f(0, 1); glVertex3f( -pos, -pos,  pos );
        glTexCoord2f(1, 1); glVertex3f(  pos, -pos,  pos );
        glTexCoord2f(1, 0); glVertex3f(  pos, -pos, -pos );
        glEnd();
    }

   glPopAttrib();
   glPopMatrix();

}
