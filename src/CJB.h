#ifndef CJB_H
#define CJB_H

#include <stdio.h>
#include <Windows.h>
#include "bmp.h"
#include "text_data.h"

BYTE encrypth_blue_color(float ratio, BYTE red, BYTE green, BYTE blue, BYTE encBit);
void encrypt_using_CJB(BITMAPDATA *imageData, TEXTDATA *textData);
void decrypt_using_CJB(BITMAPDATA *imageData, TEXTDATA *textData);

#endif