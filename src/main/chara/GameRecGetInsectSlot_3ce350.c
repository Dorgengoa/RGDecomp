#include "types.h"

/* Asymmetric guard pair over fifteen 0x34-byte records at +0x00.  Retail's
   `sll 1 / addu / sll 2 / addu / sll 2` is mwcc's strength reduction of
   *0x34 as ((index*3)*4 + index)*4. */

typedef struct Owner34 {
    u8 rec[1];         /* +0x00, 0x34 bytes each */
} Owner34;

void *GameRecGetInsectSlot_3ce350(Owner34 *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 0xF;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &o->rec[index * 0x34];
}
