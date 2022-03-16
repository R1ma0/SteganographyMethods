#include "LSB.h"

void encrypt_using_LSB(BITMAPDATA *data, TEXTDATA *encData)
{    
    DWORD bitSeqLength = encData->textLength * 8;

    // Checking enough pixels to encrypt the text

    DWORD bytePerImage = data->bmInfo.biHeight * data->bmBytePerLine;
    DWORD needBytesPerImage = bitSeqLength / encData->bitPerByte;

    if(needBytesPerImage > bytePerImage)
    {
        perror("The number of pixels of the image is not enough for encryption. ");
        exit(EXIT_FAILURE);
    }

    // CHAR sequence to BIT sequence

    DWORD bitSeqId = 0;
    BYTE *bitSeq = (BYTE *) malloc (bitSeqLength * sizeof(BYTE));
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

    // Encryption
    
    int bitToWriteIndex = 1;
    WORD pixelToWriteIndex = 0;

    for(DWORD index = 0; index < bitSeqLength; index++)
    {
        write_bit(&data->bmPixelData[pixelToWriteIndex], bitSeq[index], bitToWriteIndex);
        bitToWriteIndex--;

        if(bitToWriteIndex == -1)
        {
            bitToWriteIndex = 1;
            pixelToWriteIndex++;
        }
    }

    // Memory freeing

    free(bitSeq);
}

void decrypt_using_LSB(BITMAPDATA *data, TEXTDATA *decryptionData)
{
    // BMPPIXELINFO *currPixel;
    // DWORD bitSeqLength = decryptionData->textLength * 8;
    // DWORD bitSeqId = 0;
    // BYTE *bitSeq = (BYTE *) malloc (bitSeqLength * sizeof(BYTE));

    // // Decryption

    // for(DWORD pixelId = 0; pixelId < decryptionData->textLength; pixelId++)
    // {
    //     currPixel = data->bmPixelInfo[pixelId];

    //     for(WORD decBitId = 0; decBitId < decryptionData->bitPerByte; decBitId++)
    //     {
    //         bitSeq[bitSeqId++] = read_bit(currPixel->rgbBlue, 7 - decBitId);
    //     }

    //     for(WORD decBitId = 0; decBitId < decryptionData->bitPerByte; decBitId++)
    //     {
    //         bitSeq[bitSeqId++] = read_bit(currPixel->rgbGreen, 7 - decBitId);
    //     }

    //     for(WORD decBitId = 0; decBitId < decryptionData->bitPerByte; decBitId++)
    //     {
    //         bitSeq[bitSeqId++] = read_bit(currPixel->rgbRed, 7 - decBitId);
    //     }
    // }

    // BIT sequence to CHAR sequence

    // for(int i = 0; i < 7; i++)
    // {
    //     printf("%c", bitSeq[i]);
    // }

    // Memory freeing

    // free(bitSeq);
}

void write_bit(BYTE *color, BYTE bit, WORD position)
{
    if (bit == 1)
    {
        *color |= (1 << position);
    }
    else
    {
        *color &= ~(1 << position);
    }
}

BYTE read_bit(BYTE color, WORD position)
{
    if(color & (1 << position))
    {
        return '1';
    }

    return '0';
}