/**
 * ReadTGA.hpp
 *
 *  @date 13.12.2011
 *  @author Thomas Wiemann
 *  @source http://content.gpwiki.org/index.php/LoadTGACpp
 */

#ifndef READTGA_HPP_
#define READTGA_HPP_

#include <iostream>
#include <fstream>
#include <memory.h>

#define IMG_OK 0x1
#define IMG_ERR_NO_FILE 0x2
#define IMG_ERR_MEM_FAIL 0x4
#define IMG_ERR_BAD_FORMAT 0x8
#define IMG_ERR_UNSUPPORTED 0x40

class ReadTGA

{
public:
    ReadTGA();
    ~ReadTGA();
    int load(const char* filename);
    int getBitsPerPixel();
    int width();
    int height();
    unsigned char* data();       // Return a pointer to image data
    unsigned char* palette();   // Return a pointer to VGA palette

private:
    short int       m_width;
    short int       m_height;
    short int       m_bpp;

    unsigned long   m_imageSize;
    char            m_enc;
    unsigned char*  m_image;
    unsigned char*  m_palette;
    unsigned char*  m_paletteData;

    // Internal workers
    int readHeader();
    int loadRawData();
    int loadRLEData();
    int loadTgaPalette();
    void BGRtoRGB();
    void FlipImg();
};







#endif /* READTGA_HPP_ */
