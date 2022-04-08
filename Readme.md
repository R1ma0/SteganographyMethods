# COMPILATION (IN THE TERMINAL)
1. make clean
2. make

---

# LAUNCH (IN THE TERMINAL)
## Embedding
- LSB: IOSM.exe -e -LSB chunk ptrf ptsf ptet ptdd
> **Example:** *IOSM.exe -e -LSB 2 tests/image.bmp tests/enc_image.bmp tests/forEncryption.txt tests/dataForDecryption.txt*
- KJB: IOSM.exe -e -LSB ptk ptrf ptsf ptet ptdd
> **Example:** *IOSM.exe -e -KJB tests/key.txt tests/image.bmp tests/enc_image.bmp tests/forEncryption.txt tests/dataForDecryption.txt*
## Reading
- LSB: IOSM.exe -d -LSB ptrf ptdd ptdt
> **Example:** *IOSM.exe -d -LSB tests/enc_image.bmp tests/dataForDecryption.txt tests/decryptedText.txt*
- KJB: IOSM.exe -d -KJB ptrf ptdd ptdt ptk
> **Example:** *IOSM.exe -d -KJB tests/enc_image.bmp tests/dataForDecryption.txt tests/decryptedText.txt tests/key.txt*

# Designations
*-e* - embedding \
*-d* - reading \
*chunk* - for LSB the number of lower bits (from 1 to 4) \
*ptrf* - the path to the original image in .bmp format \
*ptsf* - the path to save the image in .bmp format \
*ptet* - the path to the encrypted text \
*ptdt* - the path to save the decrypted text \
*ptdd* - the path to the data to decrypt (the number of lower bits and the length of the ciphertext) \
*ptk* - the path to the file with the key 
