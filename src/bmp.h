#ifndef BMP_H
#define BMP_H

#include <Windows.h>

typedef struct tagBITMAPDATA
{
    // The energy of the embedded data bit.
    // The more, the more noticeable and the less
    // distortion during decryption. 
    double energy;
    UINT bmBytePerLine;
    BITMAPFILEHEADER bmHeader;
    BITMAPINFOHEADER bmInfo;
    BYTE *bmPixelData;
} BITMAPDATA;

#endif