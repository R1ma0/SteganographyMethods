#include "bit_rw.h"

void write_bit(BYTE *element, BYTE bit, WORD position)
{
    if (bit == 1)
    {
        *element |= (1 << position);
    }
    else
    {
        *element &= ~(1 << position);
    }
}

BYTE read_bit(BYTE *element, WORD position)
{
    if(*element & (1 << position))
    {
        return 1;
    }

    return 0;
}