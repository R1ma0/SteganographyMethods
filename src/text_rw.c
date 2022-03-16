#include "text_rw.h"

void write_data_for_text_encryption_to_file(unsigned long textLength, unsigned int lowerBitsNum, char *decryptionDataFilename)
{
    FILE *fp;

    // Opening

    fp = fopen(decryptionDataFilename, "w");
    if(fp == NULL)
    {
        perror("File writing error.\n");
        exit(EXIT_FAILURE);
    }

    // Writing

    fprintf(fp, "%d\n", lowerBitsNum);
    fprintf(fp, "%d", textLength);

    // Closing

    fclose(fp);
}

void read_data_to_encrypt_text_from_file(char *decryptionDataFilename, TEXTDATA *decryptionData)
{
    FILE *fp;

    // Opening

    fp = fopen(decryptionDataFilename, "r");
    if(fp == NULL)
    {
        perror("Decryption data reading error.\n");
        exit(EXIT_FAILURE);
    }

    // Reading

    fscanf(fp, "%d", &decryptionData->bitPerByte);
    fscanf(fp, "%d", &decryptionData->textLength);

    // Closing

    fclose(fp);
}

void read_text_for_encryption_from_file(char *pathToFile, TEXTDATA *encryptionData)
{
    FILE *fp;
    
    // Opening

    fp = fopen(pathToFile, "r");
    if(fp == NULL)
    {
        perror("File reading error.\n");
        exit(EXIT_FAILURE);
    }

    // File size

    fseek(fp, 0L, SEEK_END);
    encryptionData->textLength = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    // Memory allocation

    encryptionData->text = (unsigned char *) malloc (encryptionData->textLength * sizeof(unsigned char));

    // Reading

    for(unsigned long t = 0; t < encryptionData->textLength; t++)
    {
        encryptionData->text[t] = fgetc(fp);
    }

    // Closing

    fclose(fp);
}

// void write_decrypted_text_to_file(char *pathToFile, unsigned char *textToWrite, unsigned long *charCount)
// {
//     FILE *fp;

//     // Opening

//     fp = fopen(pathToFile, "w");
//     if(fp == NULL)
//     {
//         perror("File writing error.\n");
//         exit(EXIT_FAILURE);
//     }

//     // Writing
    
//     for(unsigned long v = 0; v < *charCount; v++)
//     {
//         fputc(textToWrite[v], fp);
//     }

//     // Closing

//     fclose(fp);
// }