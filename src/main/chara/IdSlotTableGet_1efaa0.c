#include "types.h"

/* The asymmetric guard pair: 0x100 entries of 8 bytes at +0x00. */

typedef struct Rec8b {
    s32 v;             /* +0x00 */
    s32 unk4;
} Rec8b;

s32 IdSlotTableGet_1efaa0(Rec8b *rec, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 0x100;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return rec[index].v;
}
