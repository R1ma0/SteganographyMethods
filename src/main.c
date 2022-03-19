#include "main.h"

#define KJB_MAX_EMBEDDING_AREA_SIZE 4
#define LSB_MAX_BIT_PER_BYTE 4

int main(int argc, char *argv[])
{
    BITMAPDATA bitmapData;
    TEXTDATA edData;
    DWORD chunk;
    bitmapData.energy = 0.5;

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
                edData.chunk = chunk;
                bmp_read(argv[4], &bitmapData);
                read_text_for_encryption_from_file(argv[6], &edData);
                encrypt_using_LSB(&bitmapData, &edData);
                bmp_write(argv[5], &bitmapData);
                write_data_for_text_encryption_to_file(edData.textLength, edData.chunk, argv[7]);
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
            chunk = strtol(argv[3], NULL, 10);

            if(chunk > 0 && chunk <= KJB_MAX_EMBEDDING_AREA_SIZE)
            {
                edData.chunk = chunk;
                bmp_read(argv[4], &bitmapData);
                read_text_for_encryption_from_file(argv[6], &edData);
                encrypt_using_KJB(&bitmapData, &edData);
                bmp_write(argv[5], &bitmapData);
                write_data_for_text_encryption_to_file(edData.textLength, edData.chunk, argv[7]);
            }
            else
            {
                printf(
                    "The size of the area for which the brightness \
                    will be predicted can be in the range from 1 to %d. \
                    ", KJB_MAX_EMBEDDING_AREA_SIZE
                );
                exit(EXIT_FAILURE);
            }
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
            read_data_to_encrypt_text_from_file(argv[4], &edData);
            decrypt_using_LSB(&bitmapData, &edData);
            write_decrypted_text_to_file(argv[5], edData.text, &edData.textLength);
        }
        else if(strcmp(argv[2], "-KJB") == 0) // KJB method
        {
            bmp_read(argv[3], &bitmapData);
            read_data_to_encrypt_text_from_file(argv[4], &edData);
            decrypt_using_KJB(&bitmapData, &edData);
            write_decrypted_text_to_file(argv[5], edData.text, &edData.textLength);
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

    free(edData.text);
    free(bitmapData.bmPixelData);
    
    return 0;
}
