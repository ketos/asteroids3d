#ifndef _EXPLOSION_H
#define _EXPLOSION_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

class Explosion 
{
public:
    Explosion();
    void explode(float speed);

private:
    //GLuint texture[8]; 
    //double frame;
    GLuint LoadTexture( const char * filename, int width, int height );
    void FreeTexture( GLuint texture );

};

#endif //_EXPLOSION_H
