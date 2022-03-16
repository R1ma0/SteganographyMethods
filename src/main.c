#include "main.h"

int main(int argc, char *argv[])
{
    BITMAPDATA bitmapData;
    TEXTDATA edData;

    // TO-DO: receive via argv
    char *decryptionDataFilename = "decryptionData.txt";
    edData.bitPerByte = 2; // 1 - 4
    // END TO-DO
    
    if(argc < 3)
    {
        printf("Few arguments. ");
        exit(EXIT_FAILURE);
    }
    
    // BMP reading

    bmp_read(argv[1], &bitmapData);
    read_text_for_encryption_from_file(argv[3], &edData);

    // BMP encryption

    encrypt_using_LSB(&bitmapData, &edData);
    bmp_write(argv[2], &bitmapData);
    write_data_for_text_encryption_to_file(edData.textLength, edData.bitPerByte, decryptionDataFilename);

    // BMP decryption

    read_data_to_encrypt_text_from_file(decryptionDataFilename, &edData);
    decrypt_using_LSB(&bitmapData, &edData);
    write_decrypted_text_to_file("decryptedText.txt", edData.text, &edData.textLength);

    // Memory freeing

    free(edData.text);
    free(bitmapData.bmPixelData);
    
    return 0;
}
