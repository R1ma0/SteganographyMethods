#ifndef BIT_RW_H
#define BIT_RW_H

#include <Windows.h>

void write_bit(BYTE *element, BYTE bit, WORD position);
BYTE read_bit(BYTE *element, WORD position);

#endif