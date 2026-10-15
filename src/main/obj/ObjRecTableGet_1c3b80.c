#include "types.h"

/* Asymmetric guard pair over 0x28-byte records at +0x3F80, counted at
   +0x3F7C -- the same accessor as ObjRecTableGet_1c3f60 on a different table. */

typedef struct Owner3F7C {
    u8 pad000[0x3F7C];
    s32 count;         /* +0x3F7C */
    u8 rec[1];         /* +0x3F80, 0x28 bytes each */
} Owner3F7C;

void *ObjRecTableGet_1c3b80(Owner3F7C *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < o->count;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &o->rec[index * 0x28];
}
