#ifndef BMP_READ_WRITE_H
#define BMP_READ_WRITE_H

#include <stdio.h>
#include "bmp.h"

void bmp_read(char *pathToFile, BMPDATA *data);
void bmp_write(char *pathToFile, BMPDATA *data);

#endif