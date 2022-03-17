#ifndef LSB_H
#define LSB_H

#include <stdio.h>
#include <Windows.h>
#include "bmp.h"
#include "text_data.h"
#include "bit_rw.h"

void encrypt_using_LSB(BITMAPDATA *data, TEXTDATA *encryptedText);
void decrypt_using_LSB(BITMAPDATA *data, TEXTDATA *decryptionData);

#endif