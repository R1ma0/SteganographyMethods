КОМПИЛЯЦИЯ (В ТЕРМИНАЛЕ)
1. make clean
2. make

ЗАПУСК (В ТЕРМИНАЛЕ)
Шифрование 
    LSB: IOSM.exe -e -LSB chunk ptrf ptsf ptet ptdd
        Пример: IOSM.exe -e -LSB 2 tests/file.bmp tests/enc_LSB.bmp tests/forEncryption.txt tests/dataForDecryption.txt
Дешифрование
    LSB: IOSM.exe -d -LSB ptrf ptdd ptdt
        Пример: IOSM.exe -d -LSB tests/enc_LSB.bmp tests/dataForDecryption.txt tests/decryptedText.txt

-e          - шифрование
-d          - дешифрование
chunk      - размер
                для LSB числа младших бит (от 1 до 4)
                для CJB 
ptrf       - путь к исходному изображению в формате .bmp
ptsf       - путь для сохранения изображения в формате .bmp
ptet       - путь к шифруемому тексту
ptdt       - путь для сохранения дешифрованного текста
ptdd       - путь к данным для дешифрования (число младших бит и длина зашифрованного текста)