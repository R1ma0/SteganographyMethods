#ifndef TXT_RW_H
#define TXT_RW_H

#include <stdio.h>
#include <Windows.h>
#include "enc_dec_data.h"

void write_decryption_data(unsigned long textLength, unsigned int lowerBitsNum, char *decryptionDataFilename);
void read_decryption_data(char *decryptionDataFilename, EDDATA *decryptionData);
void read_text(char *pathToFile, EDDATA *encryptedText);
// void write_text(char *pathToFile, unsigned char *textToWrite, unsigned long *charCount);

#endif