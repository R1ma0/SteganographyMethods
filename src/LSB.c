#include "LSB.h"

void encrypt_using_LSB(BITMAPDATA *data, TEXTDATA *encData)
{    
    DWORD bitSeqLength = encData->textLength * 8;

    // Checking enough pixels to encrypt the text

    BYTE checkResult = checking_enough_pixels(
        &data->bmInfo.biHeight, &data->bmBytePerLine, &bitSeqLength, &encData->bitPerByte
    );

    if(checkResult)
    {
        perror("The number of pixels of the image is not enough for encryption. ");
        exit(EXIT_FAILURE);
    }

    // CHAR sequence to BIT sequence

    BYTE *bitSeq = char_to_bit_seq(&bitSeqLength, encData);

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
    
    bit_to_char_seq(encData, bitSeq, &bitSeqLength);

    // Memory freeing

    free(bitSeq);
}