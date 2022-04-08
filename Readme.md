# КОМПИЛЯЦИЯ (В ТЕРМИНАЛЕ)
1. make clean
2. make

---

# ЗАПУСК (В ТЕРМИНАЛЕ)
## Шифрование 
- LSB: IOSM.exe -e -LSB chunk ptrf ptsf ptet ptdd
> Пример: *IOSM.exe -e -LSB 2 tests/image.bmp tests/enc_image.bmp tests/forEncryption.txt tests/dataForDecryption.txt*
- KJB: IOSM.exe -e -LSB ptk ptrf ptsf ptet ptdd
> Пример: *IOSM.exe -e -KJB tests/key.txt tests/image.bmp tests/enc_image.bmp tests/forEncryption.txt tests/dataForDecryption.txt*
## Дешифрование
- LSB: IOSM.exe -d -LSB ptrf ptdd ptdt
> **Пример:** *IOSM.exe -d -LSB tests/enc_image.bmp tests/dataForDecryption.txt tests/decryptedText.txt*
- KJB: IOSM.exe -d -KJB ptrf ptdd ptdt ptk
> **Пример:** *IOSM.exe -d -KJB tests/enc_image.bmp tests/dataForDecryption.txt tests/decryptedText.txt tests/key.txt*

# Обозначения
*-e* - шифрование \
*-d* - дешифрование \
*chunk* - для LSB число младших бит (от 1 до 4) \
*ptrf* - путь к исходному изображению в формате .bmp \
*ptsf* - путь для сохранения изображения в формате .bmp \
*ptet* - путь к шифруемому тексту \
*ptdt* - путь для сохранения дешифрованного текста \
*ptdd* - путь к данным для дешифрования (число младших бит и длина зашифрованного текста) \
*ptk* - путь к файлу с ключом 
