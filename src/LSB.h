#ifndef LSB_H
#define LSB_H

#include <stdio.h>
#include <Windows.h>
#include "bmp.h"
#include "text_data.h"

void encrypt_using_LSB(BITMAPDATA *data, TEXTDATA *encryptedText);
void decrypt_using_LSB(BITMAPDATA *data, TEXTDATA *decryptionData);
void write_bit(BYTE *element, BYTE bit, WORD position);
BYTE read_bit(BYTE *element, WORD position);

#endif