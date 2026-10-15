#include "objrec.h"

/* The third table: 0x40 records of 0x58 bytes at +0x100, with the bound a
   COMPILE-TIME constant rather than a member -- retail's `slti 0x40` against
   the `lw` the other two do. */

typedef struct Owner100 {
    u8 pad000[0x100];
    u8 rec[1];         /* +0x100, 0x58 bytes each */
} Owner100;

/* MATCHED by the shared-label guard recipe -- both guards `goto none`, and
   `none:` goes BEFORE the compute block so the compute needs its own
   `goto found`. The full derivation, the mechanism (a second predecessor is
   what leaves the `b`'s delay slot empty) and the five spellings it replaced
   are written up once, in src/world/ObjRecTableGet_1c3f60.c. */

void *RecStackGetSlot_1c4330(Owner100 *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 0x40;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &o->rec[index * 0x58];
}
