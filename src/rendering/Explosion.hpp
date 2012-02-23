#ifndef _EXPLOSION_H
#define _EXPLOSION_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

#include "io/SoundManager.hpp"

class Explosion 
{
public:
    Explosion();
    void Explode();
    

private:
    //GLuint texture[8]; 
    //double frame;
    GLuint LoadTexture( const char * filename, int width, int height );
    void FreeTexture( GLuint texture );
    void ExploLoop(float speed);

};

#endif //_EXPLOSION_H
