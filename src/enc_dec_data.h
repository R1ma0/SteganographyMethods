#ifndef ENC_DEC_DATA_H
#define ENC_DEC_DATA_H

// Encryption Decryption DATA

typedef struct EDDATA_TYPE
{
    unsigned long textLength;
    unsigned int bitPerByte;
    unsigned char *text;
} EDDATA;

#endif