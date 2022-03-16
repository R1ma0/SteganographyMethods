#ifndef BMP_READ_WRITE_H
#define BMP_READ_WRITE_H

#include <stdio.h>
#include "bmp.h"

void bmp_read(char *pathToFile, BITMAPDATA *data);
void bmp_write(char *pathToFile, BITMAPDATA *data);

#endif