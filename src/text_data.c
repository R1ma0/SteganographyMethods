#include "text_data.h"

// Checking enough pixels to encrypt the text
BYTE checking_enough_pixels(LONG *height, UINT *bytePerLine, DWORD *bitSeqLength, UINT *bitPerByte)
{
    DWORD bytePerImage = (*height) * (*bytePerLine);
    DWORD needBytesPerImage = (*bitSeqLength) / (*bitPerByte);

    if(needBytesPerImage > bytePerImage)
    {
        return 1;
    }

    return 0;
}

// CHAR sequence to BIT sequence
BYTE *char_to_bit_seq(DWORD *bitSeqLength, TEXTDATA *encData)
{
    BYTE *bitSeq = (BYTE *) malloc (*bitSeqLength * sizeof(BYTE));

    DWORD bitSeqId = 0;
    BYTE sign;

    for(DWORD signId = 0; signId < encData->textLength; signId++)
    {
        sign = encData->text[signId];

        for(short i = 7; i >= 0; i--)
        {
            bitSeq[bitSeqId] = (sign >> i) & 1u;
            bitSeqId++;
        }
    }

    return bitSeq;
}

// BIT sequence to CHAR sequence
void bit_to_char_seq(TEXTDATA *encData, BYTE *bitSeq, DWORD *bitSeqLength)
{
    encData->text = (BYTE *) malloc (encData->textLength * sizeof(BYTE));

    // Filling an array with zeros

    for(DWORD i = 0; i < encData->textLength; i++)
    {
        encData->text[i] = 0;
    }

    // Converting

    DWORD charIndex = 0;
    short position = 7;

    for(DWORD index = 0; index < *bitSeqLength; index++)
    {
        write_bit(&encData->text[charIndex], bitSeq[index], position);
        position--;

        if(position == -1)
        {
            position = 7;
            charIndex++;
        }
    }
}