// #include "LSB.h"

// void encrypt_using_LSB(BMPDATA *data, EDDATA *encryptionData)
// {    
//     // Checking enough pixels to encrypt the text

//     unsigned long pixelsPerImage = data->bmInfo.biHeight * data->bmInfo.biWidth;
//     unsigned long needPixelsPerImage = (encryptionData->textLength * 8) / encryptionData->bitPerByte;

//     if(needPixelsPerImage > pixelsPerImage)
//     {
//         perror("The number of pixels of the image is not enough for encryption.\n");
//         exit(EXIT_FAILURE);
//     }

//     // CHAR sequence to BIT sequence

//     unsigned long bitSeqLength = encryptionData->textLength * 8;
//     unsigned long bitSeqId = 0;
//     unsigned char *bitSeq = (unsigned char *) malloc (bitSeqLength * sizeof(unsigned char));
//     unsigned char sign;

//     for(unsigned long signId = 0; signId < encryptionData->textLength; signId++)
//     {
//         sign = encryptionData->text[signId];

//         for(short i = 7; i >= 0; i--)
//         {
//             bitSeq[bitSeqId] = (sign >> i) & 1u;
//             bitSeqId++;
//         }
//     }

//     // Encryption
//     for(int i = 0; i < 8; i++)
//     {
//         printf("%d", bitSeq[i]);
//     }
//     printf("\n");

//     printf("Source:\n");
//     printf("%d ", data->bmPixelInfo[0]->rgbBlue);
//     printf("%d ", data->bmPixelInfo[0]->rgbGreen);
//     printf("%d ", data->bmPixelInfo[0]->rgbRed);
//     printf("%d ", data->bmPixelInfo[1]->rgbBlue);
//     printf("\n");

//     unsigned long currBitId = 0;
//     BMPPIXELINFO *currPixel;

//     for(unsigned long pixelId = 0; pixelId < encryptionData->textLength; pixelId++)
//     {
//         currPixel = data->bmPixelInfo[pixelId];

//         for(unsigned short encBitId = 0; encBitId < encryptionData->bitPerByte; encBitId++)
//         {
//             currPixel->rgbBlue = write_bit(currPixel->rgbBlue, bitSeq[currBitId++], encBitId);
//         }

//         for(unsigned short encBitId = 0; encBitId < encryptionData->bitPerByte; encBitId++)
//         {
//             currPixel->rgbGreen = write_bit(currPixel->rgbGreen, bitSeq[currBitId++], encBitId);
//         }

//         for(unsigned short encBitId = 0; encBitId < encryptionData->bitPerByte; encBitId++)
//         {
//             currPixel->rgbRed = write_bit(currPixel->rgbRed, bitSeq[currBitId++], encBitId);
//         }
//     }

//     printf("Current:\n");
//     printf("%d ", data->bmPixelInfo[0]->rgbBlue);
//     printf("%d ", data->bmPixelInfo[0]->rgbGreen);
//     printf("%d ", data->bmPixelInfo[0]->rgbRed);
//     printf("%d ", data->bmPixelInfo[1]->rgbBlue);
//     printf("\n");

//     printf("Right:\n");
//     printf("53 48 50 28\n");
//     // 00110110 source
//     // 00110100 current
//     // 00110101 right

//     // Memory freeing

//     free(bitSeq);
// }

// void decrypt_using_LSB(BMPDATA *data, EDDATA *decryptionData)
// {
//     BMPPIXELINFO *currPixel;
//     unsigned long bitSeqLength = decryptionData->textLength * 8;
//     unsigned long bitSeqId = 0;
//     unsigned char *bitSeq = (unsigned char *) malloc (bitSeqLength * sizeof(unsigned char));

//     // Decryption

//     for(unsigned long pixelId = 0; pixelId < decryptionData->textLength; pixelId++)
//     {
//         currPixel = data->bmPixelInfo[pixelId];

//         for(unsigned short decBitId = 0; decBitId < decryptionData->bitPerByte; decBitId++)
//         {
//             bitSeq[bitSeqId++] = read_bit(currPixel->rgbBlue, 7 - decBitId);
//         }

//         for(unsigned short decBitId = 0; decBitId < decryptionData->bitPerByte; decBitId++)
//         {
//             bitSeq[bitSeqId++] = read_bit(currPixel->rgbGreen, 7 - decBitId);
//         }

//         for(unsigned short decBitId = 0; decBitId < decryptionData->bitPerByte; decBitId++)
//         {
//             bitSeq[bitSeqId++] = read_bit(currPixel->rgbRed, 7 - decBitId);
//         }
//     }

//     // BIT sequence to CHAR sequence

//     for(int i = 0; i < 7; i++)
//     {
//         printf("%c", bitSeq[i]);
//     }

//     // Memory freeing

//     free(bitSeq);
// }

// BYTE write_bit(BYTE pixelColor, unsigned char bit, unsigned short position)
// {
//     if (bit == '1')
//     {
//         return pixelColor |= (1 << position);
//     }

//     return pixelColor &= ~(1 << position);
// }

// unsigned char read_bit(BYTE pixelColor, unsigned short position)
// {
//     if(pixelColor & (1 << position))
//     {
//         return '1';
//     }

//     return '0';
// }