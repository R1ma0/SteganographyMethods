#ifndef ENC_DEC_DATA_H
#define ENC_DEC_DATA_H

#include <Windows.h>
#include "bit_rw.h"

typedef struct tagTEXTDATA
{
    // 
    DWORD key;
    // The energy of the embedded data bit.
    // The more, the more noticeable and the less
    // distortion during decryption. 
    double energy;
    DWORD textLength;
    // For LSB is encrypted number of bits per byte
    // For KJB the size fo the area for which the brightness will be predicted
    UINT chunk; 
    BYTE *text;
} TEXTDATA;

BYTE checking_enough_pixels(LONG *height, DWORD *bytePerLine, DWORD *bitSeqLength, UINT *chunk);
BYTE *char_to_bit_seq(DWORD *bitSeqLength, TEXTDATA *encData);
void bit_to_char_seq(TEXTDATA *encData, BYTE *bitSeq, DWORD *bitSeqLength);

#endif