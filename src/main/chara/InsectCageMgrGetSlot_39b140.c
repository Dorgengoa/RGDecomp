#include "types.h"

/* Asymmetric guard pair over three 0x30-byte records at +0x00; the
   `sll 1 / addu / sll 4` is *0x30 as (index*2 + index)*16. */

typedef struct Owner30 {
    u8 rec[1];         /* +0x00, 0x30 bytes each */
} Owner30;

void *InsectCageMgrGetSlot_39b140(Owner30 *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 3;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &o->rec[index * 0x30];
}
