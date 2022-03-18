#include "text_rw.h"

void write_data_for_text_encryption_to_file(DWORD textLength, UINT lowerBitsNum, char *decryptionDataFilename)
{
    FILE *fp;

    // File opening

    fp = fopen(decryptionDataFilename, "w");
    if(fp == NULL)
    {
        perror("File writing error. ");
        exit(EXIT_FAILURE);
    }

    // File writing

    fprintf(fp, "%d\n", lowerBitsNum);
    fprintf(fp, "%d", textLength);

    // Closing a file

    fclose(fp);
}

void read_data_to_encrypt_text_from_file(char *decryptionDataFilename, TEXTDATA *decryptionData)
{
    FILE *fp;

    // File opening

    fp = fopen(decryptionDataFilename, "r");
    if(fp == NULL)
    {
        perror("Decryption data reading error. ");
        exit(EXIT_FAILURE);
    }

    // File reading

    fscanf(fp, "%d", &decryptionData->chunk);
    fscanf(fp, "%d", &decryptionData->textLength);

    // Closing a file

    fclose(fp);
}

void read_text_for_encryption_from_file(char *pathToFile, TEXTDATA *encryptionData)
{
    FILE *fp;
    
    // File opening

    fp = fopen(pathToFile, "r");
    if(fp == NULL)
    {
        perror("File reading error. ");
        exit(EXIT_FAILURE);
    }

    // File size

    fseek(fp, 0L, SEEK_END);
    encryptionData->textLength = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    // Memory allocation

    encryptionData->text = (BYTE *) malloc (encryptionData->textLength * sizeof(BYTE));

    // File reading

    for(DWORD t = 0; t < encryptionData->textLength; t++)
    {
        encryptionData->text[t] = fgetc(fp);
    }

    // Closing a file

    fclose(fp);
}

void write_decrypted_text_to_file(char *pathToFile, BYTE *textToWrite, DWORD *charCount)
{
    FILE *fp;

    // File opening

    fp = fopen(pathToFile, "w");
    if(fp == NULL)
    {
        perror("File writing error. ");
        exit(EXIT_FAILURE);
    }

    // File writing
    
    for(DWORD v = 0; v < *charCount; v++)
    {
        fputc(textToWrite[v], fp);
    }

    // Closing a file

    fclose(fp);
}