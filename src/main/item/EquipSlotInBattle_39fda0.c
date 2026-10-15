#include "types.h"

/* Two-level chase off a small-data pointer, testing bits 0x1.  The likely bnel
   carries the first chase; the 0 exits behind the cold b; only
   the goto-live spelling lays it out that way (EquipSlotInBattle_39fd20). */

typedef struct Sub2_FUN_0039fda0 {
    u8 pad000[0x24C];
    u8 f;          /* +0x24C */
} Sub2_FUN_0039fda0;

typedef struct Sub_FUN_0039fda0 {
    u8 pad000[0x20];
    Sub2_FUN_0039fda0 *q;    /* +0x20 */
} Sub_FUN_0039fda0;

extern Sub_FUN_0039fda0 *D_00483748;

s32 EquipSlotInBattle_39fda0(void)
{
    Sub_FUN_0039fda0 *p;

    p = D_00483748;
    if (p != 0) {
        goto live;
    }
    return 0;
live:
    return p->q->f & 0x1;
}
