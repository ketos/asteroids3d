/**
 * ReadTGA.cpp
 *
 *  @date 13.12.2011
 *  @author Thomas Wiemann
 */

#include "ReadTGA.hpp"

ReadTGA::ReadTGA()

{
    m_image=m_palette=m_paletteData=NULL;
    m_width=m_height=m_bpp=m_enc=0;
    m_imageSize=0;
}


ReadTGA::~ReadTGA()

{
    if(m_image)
    {
        delete [] m_image;
        m_image=NULL;
    }

    if(m_palette)
    {
        delete [] m_palette;
        m_palette=NULL;
    }

    if(m_paletteData)
    {
        delete [] m_paletteData;
        m_paletteData=NULL;
    }
}


int ReadTGA::load(const char* szFilename)

{
    using namespace std;
    ifstream fIn;
    unsigned long ulSize;
    int iRet;

    // Clear out any existing image and palette
    if(m_image)
    {
        delete [] m_image;
        m_image=NULL;
    }

    if(m_palette)
    {
        delete [] m_palette;
        m_palette=NULL;
    }

    // Open the specified file
    fIn.open(szFilename,ios::binary);

    if(fIn==NULL)
        return IMG_ERR_NO_FILE;

    // Get file size
    fIn.seekg(0,ios_base::end);
    ulSize=fIn.tellg();
    fIn.seekg(0,ios_base::beg);

    // Allocate some space
    // Check and clear pDat, just in case
    if(m_paletteData)
        delete [] m_paletteData;

    m_paletteData=new unsigned char[ulSize];

    if(m_paletteData==NULL)
    {
        fIn.close();
        return IMG_ERR_MEM_FAIL;
    }

    // Read the file into memory
    fIn.read((char*)m_paletteData,ulSize);

    fIn.close();

    // Process the header
    iRet=readHeader();

    if(iRet!=IMG_OK)
        return iRet;

    switch(m_enc)
    {
    case 1: // Raw Indexed
    {
        // Check filesize against header values
        if((m_imageSize+18+m_paletteData[0]+768)>ulSize)
            return IMG_ERR_BAD_FORMAT;

        // Double check image type field
        if(m_paletteData[1]!=1)
            return IMG_ERR_BAD_FORMAT;

        // Load image data
        iRet=loadRawData();
        if(iRet!=IMG_OK)
            return iRet;

        // Load palette
        iRet=loadTgaPalette();
        if(iRet!=IMG_OK)
            return iRet;

        break;
    }

    case 2: // Raw RGB
    {
        // Check filesize against header values
        if((m_imageSize+18+m_paletteData[0])>ulSize)
            return IMG_ERR_BAD_FORMAT;

        // Double check image type field
        if(m_paletteData[1]!=0)
            return IMG_ERR_BAD_FORMAT;

        // Load image data
        iRet=loadRawData();
        if(iRet!=IMG_OK)
            return iRet;

        BGRtoRGB(); // Convert to RGB
        break;
    }

    case 9: // RLE Indexed
    {
        // Double check image type field
        if(m_paletteData[1]!=1)
            return IMG_ERR_BAD_FORMAT;

        // Load image data
        iRet=loadRLEData();
        if(iRet!=IMG_OK)
            return iRet;

        // Load palette
        iRet=loadTgaPalette();
        if(iRet!=IMG_OK)
            return iRet;

        break;
    }

    case 10: // RLE RGB
    {
        // Double check image type field
        if(m_paletteData[1]!=0)
            return IMG_ERR_BAD_FORMAT;

        // Load image data
        iRet=loadRLEData();
        if(iRet!=IMG_OK)
            return iRet;

        BGRtoRGB(); // Convert to RGB
        break;
    }

    default:
        return IMG_ERR_UNSUPPORTED;
    }

    // Check flip bit
    if((m_paletteData[17] & 0x10))
        FlipImg();

    // Release file memory
    delete [] m_paletteData;
    m_paletteData=NULL;

    return IMG_OK;
}


int ReadTGA::readHeader() // Examine the header and populate our class attributes

{
    short ColMapStart,ColMapLen;
    short x1,y1,x2,y2;

    if(m_paletteData==NULL)
        return IMG_ERR_NO_FILE;

    if(m_paletteData[1]>1)    // 0 (RGB) and 1 (Indexed) are the only types we know about
        return IMG_ERR_UNSUPPORTED;

    m_enc=m_paletteData[2];     // Encoding flag  1 = Raw indexed image
    //                2 = Raw RGB
    //                3 = Raw greyscale
    //                9 = RLE indexed
    //               10 = RLE RGB
    //               11 = RLE greyscale
    //               32 & 33 Other compression, indexed

    if(m_enc>11)       // We don't want 32 or 33
        return IMG_ERR_UNSUPPORTED;


    // Get palette info
    memcpy(&ColMapStart,&m_paletteData[3],2);
    memcpy(&ColMapLen,&m_paletteData[5],2);

    // Reject indexed images if not a VGA palette (256 entries with 24 bits per entry)
    if(m_paletteData[1]==1) // Indexed
    {
        if(ColMapStart!=0 || ColMapLen!=256 || m_paletteData[7]!=24)
            return IMG_ERR_UNSUPPORTED;
    }

    // Get image window and produce width & height values
    memcpy(&x1,&m_paletteData[8],2);
    memcpy(&y1,&m_paletteData[10],2);
    memcpy(&x2,&m_paletteData[12],2);
    memcpy(&y2,&m_paletteData[14],2);

    m_width=(x2-x1);
    m_height=(y2-y1);

    if(m_width<1 || m_height<1)
        return IMG_ERR_BAD_FORMAT;

    // Bits per Pixel
    m_bpp=m_paletteData[16];

    // Check flip / interleave byte
    if(m_paletteData[17]>32) // Interleaved data
        return IMG_ERR_UNSUPPORTED;

    // Calculate image size
    m_imageSize=(m_width * m_height * (m_bpp/8));

    return IMG_OK;
}


int ReadTGA::loadRawData() // Load uncompressed image data

{
    short iOffset;

    if(m_image) // Clear old data if present
        delete [] m_image;

    m_image=new unsigned char[m_imageSize];

    if(m_image==NULL)
        return IMG_ERR_MEM_FAIL;

    iOffset=m_paletteData[0]+18; // Add header to ident field size

    if(m_paletteData[1]==1) // Indexed images
        iOffset+=768;  // Add palette offset

    memcpy(m_image,&m_paletteData[iOffset],m_imageSize);

    return IMG_OK;
}


int ReadTGA::loadRLEData() // Load RLE compressed image data

{
    short iOffset,iPixelSize;
    unsigned char *pCur;
    unsigned long Index=0;
    unsigned char bLength,bLoop;

    // Calculate offset to image data
    iOffset=m_paletteData[0]+18;

    // Add palette offset for indexed images
    if(m_paletteData[1]==1)
        iOffset+=768;

    // Get pixel size in bytes
    iPixelSize=m_bpp/8;

    // Set our pointer to the beginning of the image data
    pCur=&m_paletteData[iOffset];

    // Allocate space for the image data
    if(m_image!=NULL)
        delete [] m_image;

    m_image=new unsigned char[m_imageSize];

    if(m_image==NULL)
        return IMG_ERR_MEM_FAIL;

    // Decode
    while(Index<m_imageSize)
    {
        if(*pCur & 0x80) // Run length chunk (High bit = 1)
        {
            bLength=*pCur-127; // Get run length
            pCur++;            // Move to pixel data

            // Repeat the next pixel bLength times
            for(bLoop=0;bLoop!=bLength;++bLoop,Index+=iPixelSize)
                memcpy(&m_image[Index],pCur,iPixelSize);

            pCur+=iPixelSize; // Move to the next descriptor chunk
        }
        else // Raw chunk
        {
            bLength=*pCur+1; // Get run length
            pCur++;          // Move to pixel data

            // Write the next bLength pixels directly
            for(bLoop=0;bLoop!=bLength;++bLoop,Index+=iPixelSize,pCur+=iPixelSize)
                memcpy(&m_image[Index],pCur,iPixelSize);
        }
    }

    return IMG_OK;
}


int ReadTGA::loadTgaPalette() // Load a 256 color palette

{
    unsigned char bTemp;
    short iIndex,iPalPtr;

    // Delete old palette if present
    if(m_palette)
    {
        delete [] m_palette;
        m_palette=NULL;
    }

    // Create space for new palette
    m_palette=new unsigned char[768];

    if(m_palette==NULL)
        return IMG_ERR_MEM_FAIL;

    // VGA palette is the 768 bytes following the header
    memcpy(m_palette,&m_paletteData[m_paletteData[0]+18],768);

    // Palette entries are BGR ordered so we have to convert to RGB
    for(iIndex=0,iPalPtr=0;iIndex!=256;++iIndex,iPalPtr+=3)
    {
        bTemp=m_palette[iPalPtr];               // Get Blue value
        m_palette[iPalPtr]=m_palette[iPalPtr+2]; // Copy Red to Blue
        m_palette[iPalPtr+2]=bTemp;             // Replace Blue at the end
    }

    return IMG_OK;
}


void ReadTGA::BGRtoRGB() // Convert BGR to RGB (or back again)

{
    unsigned long Index,nPixels;
    unsigned char *bCur;
    unsigned char bTemp;
    short iPixelSize;

    // Set ptr to start of image
    bCur=m_image;

    // Calc number of pixels
    nPixels=m_width*m_height;

    // Get pixel size in bytes
    iPixelSize=m_bpp/8;

    for(Index=0;Index!=nPixels;Index++)  // For each pixel
    {
        bTemp=*bCur;      // Get Blue value
        *bCur=*(bCur+2);  // Swap red value into first position
        *(bCur+2)=bTemp;  // Write back blue to last position

        bCur+=iPixelSize; // Jump to next pixel
    }

}


void ReadTGA::FlipImg() // Flips the image vertically (Why store images upside down?)

{
    unsigned char bTemp;
    unsigned char *pLine1, *pLine2;
    int iLineLen,iIndex;

    iLineLen=m_width*(m_bpp/8);
    pLine1=m_image;
    pLine2=&m_image[iLineLen * (m_height - 1)];

    for( ;pLine1<pLine2;pLine2-=(iLineLen*2))
    {
        for(iIndex=0;iIndex!=iLineLen;pLine1++,pLine2++,iIndex++)
        {
            bTemp=*pLine1;
            *pLine1=*pLine2;
            *pLine2=bTemp;
        }
    }

}


int ReadTGA::getBitsPerPixel()

{
    return m_bpp;
}


int ReadTGA::width()

{
    return m_width;
}


int ReadTGA::height()

{
    return m_height;
}


unsigned char* ReadTGA::data()

{
    return m_image;
}


unsigned char* ReadTGA::palette()

{
    return m_palette;
}
