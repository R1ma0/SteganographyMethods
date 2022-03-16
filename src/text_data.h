#ifndef ENC_DEC_DATA_H
#define ENC_DEC_DATA_H

#include <Windows.h>

typedef struct tagTEXTDATA
{
    DWORD textLength;
    UINT bitPerByte;
    BYTE *text;
} TEXTDATA;

#endif