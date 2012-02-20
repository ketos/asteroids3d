/**
 * ReadTIFF.hpp
 *
 *  @date 14.12.2011
 *  @author Thomas Wiemann
 */

#ifndef READTIFF_HPP_
#define READTIFF_HPP_

#include <string>
using std::string;

class ReadTIFF
{
public:
    ReadTIFF(string filename);
    virtual ~ReadTIFF();

    int width() {return m_width;}
    int height() {return m_height;}
    unsigned char* pixels() {return m_pixels;}

private:
    int m_width;
    int m_height;
    unsigned char* m_pixels;
};

#endif /* READTIFF_HPP_ */
