#ifndef BMP_H
#define BMP_H

#include <Windows.h>

typedef struct tagBITMAPDATA
{
    unsigned int bmBytePerLine;
    BITMAPFILEHEADER bmHeader;
    BITMAPINFOHEADER bmInfo;
    BYTE *bmPixelData;
} BITMAPDATA;

#endif