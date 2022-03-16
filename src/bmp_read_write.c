#include "bmp_read_write.h"

void bmp_read(char *pathToFile, BMPDATA *bitmapData)
{
    FILE *fp;
    LONG colorGridHeight;
    LONG colorGridWidth;

    fp = fopen(pathToFile, "rb");
    if(fp == NULL)
    {
        perror("File reading error.\n");
        exit(EXIT_FAILURE);
    }

    fread(&bitmapData->type, sizeof(WORD), 1, fp);
    if(bitmapData->type != 0x4d42) // BM
    {
        perror("The specified file is not a bitmap format.\n");
        exit(EXIT_FAILURE);
    }

    // Reading headlines

    fread(&bitmapData->bmHeader, sizeof(BMPFILEHEADER), 1, fp);
    fread(&bitmapData->bmInfo, sizeof(BMPINFOHEADER), 1, fp);

    // Memory allocation

    colorGridHeight = bitmapData->bmInfo.biHeight;
    colorGridWidth = bitmapData->bmInfo.biWidth;

    bitmapData->bmPixelInfo = (BMPPIXELINFO **) malloc (colorGridHeight * sizeof(BMPPIXELINFO *));
    for(LONG i = 0; i < colorGridHeight; i++)
    {
        bitmapData->bmPixelInfo[i] = (BMPPIXELINFO *) malloc (colorGridWidth * sizeof(BMPPIXELINFO));
    }

    // Colors reading

    for(LONG row = 0; row < colorGridHeight; row++)
    {
        for(LONG col = 0; col < colorGridWidth; col++)
        {
            fread(&bitmapData->bmPixelInfo[row][col], sizeof(BMPPIXELINFO), 1, fp);
        }
    }

    fclose(fp);
}

void bmp_write(char *pathToFile, BMPDATA *data)
{
    FILE *fp;

    fp = fopen(pathToFile, "wb");
    if(fp == NULL)
    {
        perror("File writing error.\n");
        exit(EXIT_FAILURE);
    }

    fwrite(&data->type, sizeof(WORD), 1, fp);
    fwrite(&data->bmHeader, sizeof(BMPFILEHEADER), 1, fp);
    fwrite(&data->bmInfo, sizeof(BMPINFOHEADER), 1, fp);

    for(LONG row = 0; row < data->bmInfo.biHeight; row++)
    {
        for(LONG col = 0; col < data->bmInfo.biWidth; col++)
        {
            fwrite(&data->bmPixelInfo[row][col], sizeof(BMPPIXELINFO), 1, fp);
        }
    }

    fclose(fp);
}