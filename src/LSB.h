#ifndef LSB_H
#define LSB_H

#include <stdio.h>
#include <Windows.h>
#include "bmp.h"
#include "enc_dec_data.h"

void encrypt_using_LSB(BMPDATA *data, EDDATA *encryptedText);
void decrypt_using_LSB(BMPDATA *data, EDDATA *decryptionData);
BYTE write_bit(BYTE pixelColor, unsigned char bit, unsigned short position);
unsigned char read_bit(BYTE pixelColor, unsigned short position);

#endif