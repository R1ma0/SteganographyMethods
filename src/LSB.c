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

void decrypt_using_LSB(BITMAPDATA *data, TEXTDATA *encData)
{
    DWORD bitSeqLength = encData->textLength * 8;
    BYTE *bitSeq = (BYTE *) malloc (bitSeqLength * sizeof(BYTE));
    encData->text = (BYTE *) malloc (encData->textLength * sizeof(BYTE));

    // Filling an array with zeros

    for(DWORD i = 0; i < encData->textLength; i++)
    {
        encData->text[i] = 0;
    }

    // Decryption

    int bitToReadIndex = 1;
    WORD pixelToReadIndex = 0;

    for(DWORD index = 0; index < bitSeqLength; index++)
    {
        bitSeq[index] = read_bit(&data->bmPixelData[pixelToReadIndex], bitToReadIndex);
        bitToReadIndex--;

        if(bitToReadIndex == -1)
        {
            bitToReadIndex = 1;
            pixelToReadIndex++;
        }
    }

    // BIT sequence to CHAR sequence
    
    DWORD charIndex = 0;
    short position = 7;

    for(DWORD index = 0; index < bitSeqLength; index++)
    {
        write_bit(&encData->text[charIndex], bitSeq[index], position);
        position--;

        if(position == -1)
        {
            position = 7;
            charIndex++;
        }
    }

    // Memory freeing

    free(bitSeq);
}