#include "KJB.h"

// energy - the energy of the embedded data bit
BYTE encrypth_blue_color(float energy, BYTE red, BYTE green, BYTE blue, BYTE encBit)
{
    UINT brightness = (red * 0.298) + (green * 0.586) + (blue * 0.114);

    if(encBit == 1)
    {
        return blue + (energy * brightness);
    }
    
    return blue - (energy * brightness);
}

void encrypt_using_KJB(BITMAPDATA *imageData, TEXTDATA *textData)
{
    DWORD bitSeqLength = textData->textLength * 8;

    // CHAR sequence to BIT sequence

    BYTE *bitSeq = char_to_bit_seq(&bitSeqLength, textData);

    // Two-dimesional array for pixels
    // Converting a one-dimensional array to two-dimensional 
    // one for easy rewriting of colors (mdaaaaa ;)

    UINT pixelsPerLine = imageData->bmBytePerLine / 3;
    RGBQUAD **pixels = (RGBQUAD **) malloc (imageData->bmInfo.biHeight * sizeof(RGBQUAD *));
    for(UINT i = 0; i < imageData->bmInfo.biHeight; i++)
    {
        pixels[i] = (RGBQUAD *) malloc (pixelsPerLine * sizeof(RGBQUAD));
    }

    DWORD pixelIndex = 0;

    for(UINT i = 0; i < imageData->bmInfo.biHeight; i++)
    {
        for(UINT j = 0; j < pixelsPerLine; j++)
        {
            pixels[i][j].rgbBlue = imageData->bmPixelData[pixelIndex++];
            pixels[i][j].rgbGreen = imageData->bmPixelData[pixelIndex++];
            pixels[i][j].rgbRed = imageData->bmPixelData[pixelIndex++];
        }
    }

    // Encryption

    UINT step = textData->chunk + 1;
    DWORD row = step;
    DWORD col = step;

    for(DWORD bitID = 0; bitID < bitSeqLength; bitID++)
    {
        pixels[row][col].rgbBlue = encrypth_blue_color(\
            imageData->energy, \
            pixels[row][col].rgbRed, \
            pixels[row][col].rgbGreen, \
            pixels[row][col].rgbBlue, \
            bitSeq[bitID]
        );
        
        if((col + step) < (imageData->bmBytePerLine - step))
        {
            col += step;
        }
        else
        {
            col = step;
            row += step;
        }
    }

    // Two-dimensional array to one-dimensional array

    pixelIndex = 0;

    for(UINT i = 0; i < imageData->bmInfo.biHeight; i++)
    {
        for(UINT j = 0; j < pixelsPerLine; j++)
        {
            imageData->bmPixelData[pixelIndex++] = pixels[i][j].rgbBlue;
            imageData->bmPixelData[pixelIndex++] = pixels[i][j].rgbGreen;
            imageData->bmPixelData[pixelIndex++] = pixels[i][j].rgbRed;
        }
    }

    // Memory freeing

    free(bitSeq);
    for(UINT i = 0; i < imageData->bmInfo.biHeight; i++)
    {
        free(pixels[i]);
    }
    free(pixels);
}

void decrypt_using_KJB(BITMAPDATA *imageData, TEXTDATA *textData)
{
    DWORD bitSeqLength = textData->textLength * 8;
    BYTE *bitSeq = (BYTE *) malloc (bitSeqLength * sizeof(BYTE));

    // Two-dimesional array for pixels

    UINT pixelsPerLine = imageData->bmBytePerLine / 3;

    RGBQUAD **pixels = (RGBQUAD **) malloc (imageData->bmInfo.biHeight * sizeof(RGBQUAD *));
    for(UINT i = 0; i < imageData->bmInfo.biHeight; i++)
    {
        pixels[i] = (RGBQUAD *) malloc (pixelsPerLine * sizeof(RGBQUAD));
    }

    DWORD pixelIndex = 0;

    for(UINT i = 0; i < imageData->bmInfo.biHeight; i++)
    {
        for(UINT j = 0; j < pixelsPerLine; j++)
        {
            pixels[i][j].rgbBlue = imageData->bmPixelData[pixelIndex++];
            pixels[i][j].rgbGreen = imageData->bmPixelData[pixelIndex++];
            pixels[i][j].rgbRed = imageData->bmPixelData[pixelIndex++];
        }
    }

    // Decryption

    UINT step = textData->chunk + 1;
    DWORD row = step;
    DWORD col = step;
    RGBQUAD currPixel;
    double estimatedBrightness = 0;
    double bluePixelsSum = 0;

    for(DWORD bitID = 0; bitID < bitSeqLength; bitID++)
    {
        currPixel = pixels[row][col];

        for(UINT i = 1; i <= textData->chunk; i++)
        {
            bluePixelsSum += pixels[row][col + i].rgbBlue;
            bluePixelsSum += pixels[row][col - i].rgbBlue;
            bluePixelsSum += pixels[row + i][col].rgbBlue;
            bluePixelsSum += pixels[row - i][col].rgbBlue;
        }

        estimatedBrightness = bluePixelsSum / (4 * textData->chunk);
        bluePixelsSum = 0;

        // Set bit value

        if(currPixel.rgbBlue > estimatedBrightness)
        {
            bitSeq[bitID] = 1;
        }
        else
        {
            bitSeq[bitID] = 0;
        }

        // Next pixel
        
        if((col + step) < (imageData->bmBytePerLine - step))
        {
            col += step;
        }
        else
        {
            col = step;
            row += step;
        }
    }

    // BIT sequence to CHAR sequence
    
    bit_to_char_seq(textData, bitSeq, &bitSeqLength);

    // Memory freeing

    free(bitSeq);
    for(UINT i = 0; i < imageData->bmInfo.biHeight; i++)
    {
        free(pixels[i]);
    }
    free(pixels);
}