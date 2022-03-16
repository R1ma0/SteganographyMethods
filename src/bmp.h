#ifndef BMP_H
#define BMP_H

#include <Windows.h>

typedef struct BMPFILEHEADER_TYPE
{
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BMPFILEHEADER;

typedef struct BMPINFOHEADER_TYPE
{
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BMPINFOHEADER;

typedef struct BMPPIXELINFO_TYPE
{
    BYTE colors[4];
    // BYTE rgbBlue;
    // BYTE rgbGreen;
    // BYTE rgbRed;
    // BYTE reserved;
} BMPPIXELINFO;

typedef struct BMPDATA_TYPE
{
    WORD type;
    BMPFILEHEADER bmHeader;
    BMPINFOHEADER bmInfo;
    BMPPIXELINFO **bmPixelInfo;
} BMPDATA;

#endif