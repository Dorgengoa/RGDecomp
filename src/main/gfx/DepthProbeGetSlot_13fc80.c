#include "types.h"

/* The asymmetric guard pair again: 4 entries of 0x10 bytes at +0x3CD0. */

typedef struct Owner3CD0 {
    u8 pad000[0x3CD0];
    u8 rec[1];         /* +0x3CD0, 0x10 bytes each */
} Owner3CD0;

void *DepthProbeGetSlot_13fc80(Owner3CD0 *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 4;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &o->rec[index * 0x10];
}
