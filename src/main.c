#include "main.h"

int main(int argc, char *argv[])
{
    BITMAPDATA bitmapData;
    TEXTDATA edData;

    if(strcmp(argv[1], "-e") == 0) // Encryption mode
    {
        if(strcmp(argv[2], "-LSB") == 0) // LSB method
        {
            DWORD chunk = strtol(argv[3], NULL, 10);

            if(chunk < 5 && chunk > 0) // range {1; 4}
            {
                edData.bitPerByte = chunk;
                bmp_read(argv[4], &bitmapData);
                read_text_for_encryption_from_file(argv[6], &edData);
                encrypt_using_LSB(&bitmapData, &edData);
                bmp_write(argv[5], &bitmapData);
                write_data_for_text_encryption_to_file(edData.textLength, edData.bitPerByte, argv[7]);
            }
            else
            {
                perror("Chunk size must be from 1 to 4. ");
                exit(EXIT_FAILURE);
            }
        }   
        else if(strcmp(argv[2], "-CJB") == 0) // CJB method
        {
            perror("'-CJB' unavailable. ");
            exit(EXIT_FAILURE);
        }
        else
        {
            perror("Use '-LSB' or '-CJB' flags. ");
            exit(EXIT_FAILURE);
        }
    }
    else if(strcmp(argv[1], "-d") == 0) // Decryption mode
    {
        if(strcmp(argv[2], "-LSB") == 0)
        {
            bmp_read(argv[3], &bitmapData);
            read_data_to_encrypt_text_from_file(argv[4], &edData);
            decrypt_using_LSB(&bitmapData, &edData);
            write_decrypted_text_to_file(argv[5], edData.text, &edData.textLength);
        }
        else if(strcmp(argv[2], "-CJB") == 0) // CJB method
        {

        }
        else
        {
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        perror("Use '-e' for encryption or '-d' for decryption flags. ");
        return 1;
    }

    // TO-DO: receive via argv
    // char *decryptionDataFilename = "decryptionData.txt";
    // edData.bitPerByte = 2; // 1 - 4
    // END TO-DO
    
    // BMP reading

    // bmp_read(argv[1], &bitmapData);
    // read_text_for_encryption_from_file(argv[3], &edData);

    // BMP encryption

    // encrypt_using_LSB(&bitmapData, &edData);
    // bmp_write(argv[2], &bitmapData);
    // write_data_for_text_encryption_to_file(edData.textLength, edData.bitPerByte, decryptionDataFilename);

    // BMP decryption

    // read_data_to_encrypt_text_from_file(decryptionDataFilename, &edData);
    // decrypt_using_LSB(&bitmapData, &edData);
    // write_decrypted_text_to_file("decryptedText.txt", edData.text, &edData.textLength);

    // Memory freeing

    free(edData.text);
    free(bitmapData.bmPixelData);
    
    return 0;
}
