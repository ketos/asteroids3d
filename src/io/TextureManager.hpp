#ifndef _TEXTURMANAGER_H
#define _TEXTURMANAGER_H

#include <QtOpenGL>

class TextureManager
{
public:
    static GLuint LoadTexture(const char *TexName);

};

#endif