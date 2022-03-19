#ifndef TXT_RW_H
#define TXT_RW_H

#include <stdio.h>
#include <Windows.h>
#include "text_data.h"

void write_data_for_text_encryption_to_file(DWORD textLength, UINT lowerBitsNum, char *decryptionDataFilename);
void read_data_to_encrypt_text_from_file(char *decryptionDataFilename, TEXTDATA *decryptionData);
void read_text_for_encryption_from_file(char *pathToFile, TEXTDATA *encryptedText);
void write_decrypted_text_to_file(char *pathToFile, BYTE *textToWrite, DWORD *charCount);
void read_key_KJB(char *pathToFile, DWORD *key);
void write_key_KJB(char *pathToFile, DWORD *key);

#endif