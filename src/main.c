#include "main.h"

#define KJB_MAX_EMBEDDING_AREA_SIZE 4
#define LSB_MAX_BIT_PER_BYTE 4

int main(int argc, char *argv[])
{
    BITMAPDATA bitmapData;
    TEXTDATA textData;
    DWORD chunk;
    textData.chunk = 2; // Default
    textData.energy = 0.5; // Default

    //
    // TO-DO: MAKE IF BEAUTIFUL !!!
    //

    if(strcmp(argv[1], "-e") == 0) // Encryption mode
    {
        if(strcmp(argv[2], "-LSB") == 0) // LSB method
        {
            chunk = strtol(argv[3], NULL, 10);

            if(chunk > 0 && chunk <= LSB_MAX_BIT_PER_BYTE)
            {
                textData.chunk = chunk;
                bmp_read(argv[4], &bitmapData);
                read_text_for_encryption_from_file(argv[6], &textData);
                encrypt_using_LSB(&bitmapData, &textData);
                bmp_write(argv[5], &bitmapData);
                write_data_for_text_encryption_to_file(textData.textLength, textData.chunk, argv[7]);
            }
            else
            {
                printf(
                    "The number of encrypted bits can be in the \
                    range from 1 to %d. ", LSB_MAX_BIT_PER_BYTE
                );
                exit(EXIT_FAILURE);
            }
        }   
        else if(strcmp(argv[2], "-KJB") == 0) // KJB method
        {
            bmp_read(argv[4], &bitmapData);
            read_text_for_encryption_from_file(argv[6], &textData);
            encrypt_using_KJB(&bitmapData, &textData);
            bmp_write(argv[5], &bitmapData);
            write_data_for_text_encryption_to_file(textData.textLength, textData.chunk, argv[7]);
            write_key_KJB(argv[3], &textData.key);
        }
        else
        {
            printf("Use '-LSB' or '-KJB' flags. ");
            exit(EXIT_FAILURE);
        }
    }
    else if(strcmp(argv[1], "-d") == 0) // Decryption mode
    {
        if(strcmp(argv[2], "-LSB") == 0)
        {
            bmp_read(argv[3], &bitmapData);
            read_data_to_encrypt_text_from_file(argv[4], &textData);
            decrypt_using_LSB(&bitmapData, &textData);
            write_decrypted_text_to_file(argv[5], textData.text, &textData.textLength);
        }
        else if(strcmp(argv[2], "-KJB") == 0) // KJB method
        {
            bmp_read(argv[3], &bitmapData);
            read_data_to_encrypt_text_from_file(argv[4], &textData);
            read_key_KJB(argv[6], &textData.key);
            decrypt_using_KJB(&bitmapData, &textData);
            write_decrypted_text_to_file(argv[5], textData.text, &textData.textLength);
        }
        else
        {
            printf("Use '-LSB' or '-KJB' flags. ");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        printf("Use '-e' for encryption or '-d' for decryption flags. ");
        exit(EXIT_FAILURE);
    }

    // Memory freeing

    free(textData.text);
    free(bitmapData.bmPixelData);
    
    return 0;
}
