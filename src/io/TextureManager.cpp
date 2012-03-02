/**
*   @file TextureManager.cpp
*   @author gruppe3
*/

#include "io/TextureManager.hpp"

GLuint TextureManager::LoadTexture(const char *TexName)
{
   ReadTGA Img;        // Image loader
   GLuint Texture;
 
  // Load our Texture
   if(Img.load(TexName)!=IMG_OK)
    return -1;
 
   glGenTextures(1,&Texture);            // Allocate space for texture
   glBindTexture(GL_TEXTURE_2D,Texture); // Set our Tex handle as current
 
   // Create the texture
    if(Img.getBitsPerPixel()==24)
     glTexImage2D(GL_TEXTURE_2D,0,3,Img.width(),Img.height(),0,
                  GL_RGB,GL_UNSIGNED_BYTE,Img.data());
    else if(Img.getBitsPerPixel()==32)
     glTexImage2D(GL_TEXTURE_2D,0,4,Img.width(),Img.height(),0,
                  GL_RGBA,GL_UNSIGNED_BYTE,Img.data());
    else
     return -1;
 
   // Specify filtering and edge actions
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
 
   return Texture;
}