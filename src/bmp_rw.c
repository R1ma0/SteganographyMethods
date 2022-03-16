#include "bmp_rw.h"

void bmp_read(char *pathToFile, BITMAPDATA *data)
{
    FILE *fp;

    // File reading 

    fp = fopen(pathToFile, "rb");
    if(fp == NULL)
    {
        perror("Error reading file. ");
        exit(EXIT_FAILURE);
    }

    // Checking file format

    fread(&data->bmHeader.bfType, sizeof(WORD), 1, fp);
    if(data->bmHeader.bfType != 0x4d42) // BM
    {
        perror("The specified file is not a bitmap format.\n");
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_SET);

    // Reading headlines

    fread(&data->bmHeader, sizeof(BITMAPFILEHEADER), 1, fp);
    fread(&data->bmInfo, sizeof(BITMAPINFOHEADER), 1, fp);

    // Memory allocation

    data->bmBytePerLine = (data->bmInfo.biWidth * data->bmInfo.biBitCount / 8 + 3) / 4 * 4;
    data->bmPixelData = (BYTE *) malloc (data->bmInfo.biHeight * data->bmBytePerLine);

    // Colors reading

    for(LONG index = 0; index < data->bmInfo.biHeight * data->bmBytePerLine; index++)
    {
        fread(&data->bmPixelData[index], sizeof(BYTE), 1, fp);
    }

    // Closing a file

    fclose(fp);
}

void bmp_write(char *pathToFile, BITMAPDATA *data)
{
    FILE *fp;

    // File reading

    fp = fopen(pathToFile, "wb");
    if(fp == NULL)
    {
        perror("Error writing file.");
        exit(EXIT_FAILURE);
    }

    // Data writing

    fwrite(&data->bmHeader, sizeof(BITMAPFILEHEADER), 1, fp);
    fwrite(&data->bmInfo, sizeof(BITMAPINFOHEADER), 1, fp);

    for(LONG index = 0; index < data->bmInfo.biHeight * data->bmBytePerLine; index++)
    {
        fwrite(&data->bmPixelData[index], sizeof(BYTE), 1, fp);
    }

    // Closing a file

    fclose(fp);
}