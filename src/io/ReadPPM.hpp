/**
 * ReadPPM.hpp
 *
 *  @date 11.12.2011
 *  @author Thomas Wiemann
 */

#ifndef READPPM_HPP_
#define READPPM_HPP_

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using std::string;
using std::ifstream;
using std::stringstream;
using std::cout;
using std::endl;

/**
 * @brief   Reads a .ppm-File in ASCII-Format (P4)
 */
class ReadPPM
{
public:

    /**
     * @brief   Trys to parse the given file
     */
    ReadPPM(string filename);

    /**
     * @brief   Dtor.
     */
    virtual ~ReadPPM() {};

    /**
     * @brief   Returns the height of the image
     */
    int getHeight() const { return m_height;}

    /**
     * @brief   Returns the width of the image
     */
    int getWidth() const { return m_width;}


    /**
     * @brief   Returns the pixel data
     */
    unsigned char* getPixels() const
    {
        return m_pixels;
    }

private:

    /**
     * @brief   Reads a new line from the given stream that is no
     *          comment
     *
     * @param   in      The stream to read from
     * @param   buffer  The extracted information
     */
    void readLine(ifstream & in, char* buffer);

    /// The width of the image
    int                 m_width;

    /// The height of the image
    int                 m_height;

    /// The image data
    unsigned char*      m_pixels;
};

#endif /* READPPM_HPP_ */
