#ifndef ENC_DEC_DATA_H
#define ENC_DEC_DATA_H

#include <Windows.h>
#include "bit_rw.h"

typedef struct tagTEXTDATA
{
    DWORD textLength;
    UINT bitPerByte;
    BYTE *text;
} TEXTDATA;

BYTE checking_enough_pixels(LONG *height, UINT *bytePerLine, DWORD *bitSeqLength, UINT *bitPerByte);
BYTE *char_to_bit_seq(DWORD *bitSeqLength, TEXTDATA *encData);
void bit_to_char_seq(TEXTDATA *encData, BYTE *bitSeq, DWORD *bitSeqLength);

#endif