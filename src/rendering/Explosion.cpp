#include "rendering/Explosion.hpp"

float frame = 0;
GLuint texture[8];

Explosion::Explosion()
{
    texture[0] = LoadTexture( "1.raw", 256, 256 );
    texture[1] = LoadTexture( "2.raw", 256, 256 );
    texture[2] = LoadTexture( "3.raw", 256, 256 );
    texture[3] = LoadTexture( "4.raw", 256, 256 );
    texture[4] = LoadTexture( "5.raw", 256, 256 );
    texture[5] = LoadTexture( "6.raw", 256, 256 );
    texture[6] = LoadTexture( "7.raw", 256, 256 );
    texture[7] = LoadTexture( "8.raw", 256, 256 );
    texture[8] = LoadTexture( "9.raw", 256, 256 );
}

GLuint Explosion::LoadTexture( const char * filename, int width, int height )
{
    GLuint temp;
    unsigned char * data;
    FILE* file;

    //The following code will read in our RAW file
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    data = (unsigned char *)malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );

    glGenTextures( 1, &temp ); //generate the texture with the loaded data
    glBindTexture( GL_TEXTURE_2D, temp ); //bind the texture to it’s array
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //set texture environment parameters

    //here we are setting what textures to use and when. The MIN filter is which quality to show
    //when the texture is near the view, and the MAG filter is which quality to show when the texture
    //is far from the view.

    //The qualities are (in order from worst to best)
    //GL_NEAREST
    //GL_LINEAR
    //GL_LINEAR_MIPMAP_NEAREST
    //GL_LINEAR_MIPMAP_LINEAR

    //And if you go and use extensions, you can use Anisotropic filtering textures which are of an
    //even better quality, but this will do for now.
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );

    //Here we are setting the parameter to repeat the texture instead of clamping the texture
    //to the edge of our shape. 
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    //Generate the texture with mipmaps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
    free( data ); //free the texture
    return temp; //return whether it was successfull
}

void Explosion::FreeTexture( GLuint texture )
{
  glDeleteTextures( 1, &texture );
}

void Explosion::explode(float speed) {
    glBindTexture( GL_TEXTURE_2D, texture[(int)frame] );
    glScalef(2,2,1);
    glBegin (GL_QUADS);
    glTexCoord2d(0,0);
    glVertex3f(-1,1,0);
    glTexCoord2d(1,0);
    glVertex3f(1,1,0);
    glTexCoord2d(1,1);
    glVertex3f(1,-1,0);
    glTexCoord2d(0,1);
    glVertex3f(-1,-1,0);
    glEnd();
    
    frame+=speed;
    if (frame > 8)
    {
    frame = 1;
    }
}
