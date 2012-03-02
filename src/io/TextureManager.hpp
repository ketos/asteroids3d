/**
*   @file TextureManager.hpp
*   @author gruppe3
*/

#ifndef _TEXTURMANAGER_H
#define _TEXTURMANAGER_H

#include <QtOpenGL>
#include "io/ReadTGA.hpp" 

/**
*   @brief Die Klasse TextureManager ist zum laden eines TGA bildes mit Alpha Kanal
*/
class TextureManager
{
public:
    /**
    *   @brief loads the given tga file an converts it to GLUint
    *   @param TexName string to the file
    *   @return The Texture as GLuint
    */
    static GLuint LoadTexture(const char *TexName);

};

#endif