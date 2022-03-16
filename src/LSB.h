#ifndef LSB_H
#define LSB_H

#include <stdio.h>
#include <Windows.h>
#include "bmp.h"
#include "text_data.h"

void encrypt_using_LSB(BITMAPDATA *data, TEXTDATA *encryptedText);
void decrypt_using_LSB(BITMAPDATA *data, TEXTDATA *decryptionData);
BYTE write_bit(BYTE pixelColor, unsigned char bit, unsigned short position);
unsigned char read_bit(BYTE pixelColor, unsigned short position);

#endif