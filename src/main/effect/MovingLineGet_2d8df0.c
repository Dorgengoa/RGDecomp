#include "types.h"

/* Asymmetric guard pair over 0x18 records of 0x150 bytes in a static array. */

typedef struct Rec150 { u8 bytes[0x150]; } Rec150;

extern Rec150 D_004E4190[];

void *MovingLineGet_2d8df0(s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 0x18;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &D_004E4190[index];
}
