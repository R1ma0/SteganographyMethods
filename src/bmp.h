#ifndef BMP_H
#define BMP_H

#include <Windows.h>

typedef struct tagBITMAPDATA
{
    UINT bmBytePerLine;
    BITMAPFILEHEADER bmHeader;
    BITMAPINFOHEADER bmInfo;
    BYTE *bmPixelData;
} BITMAPDATA;

#endif