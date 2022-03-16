#include "main.h"

int main(int argc, char *argv[])
{
    BITMAPDATA bitmapData;
    // EDDATA edData;

    // char *pathToFile = argv[3];
    // char *decryptionDataFilename = "decryptionData.txt";

    // edData.bitPerByte = 2; // 1 - 4
    
    // if(argc < 3)
    // {
    //     printf("Few arguments\n");
    //     exit(EXIT_FAILURE);
    // }
    
    // BMP reading

    bmp_read(argv[1], &bitmapData);
    // read_text(pathToFile, &edData);

    // BMP encryption

    // encrypt_using_LSB(&bitmapData, &edData);
    bmp_write(argv[2], &bitmapData);
    // write_decryption_data(edData.textLength, edData.bitPerByte, decryptionDataFilename);

    // BMP decryption

    // read_decryption_data(decryptionDataFilename, &edData);
    // decrypt_using_LSB(&bitmapData, &edData);

    // Memory freeing

    // free(edData.text);
    free(bitmapData.bmPixelData);
    
    return 0;
}
