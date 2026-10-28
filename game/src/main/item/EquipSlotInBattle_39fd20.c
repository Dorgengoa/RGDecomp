/* rgp:protos */
#define RGP_SELF_EquipSlotInBattle_39fd20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Two-level chase off a small-data pointer, testing bit 0 at the end.  The
   likely bnel carries the FIRST chase in its delay slot and the 0 goes cold
   behind the b. */

typedef struct Sub2_FUN_0039fd20 {
    u8 pad000[0x24C];
    u8 flags;          /* +0x24C */
} Sub2_FUN_0039fd20;

typedef struct Sub_FUN_0039fd20 {
    u8 pad000[0x20];
    Sub2_FUN_0039fd20 *q;  /* +0x20 */
} Sub_FUN_0039fd20;

extern Sub_FUN_0039fd20 *D_00483748;

s32 EquipSlotInBattle_39fd20(void)
{
    Sub_FUN_0039fd20 *p;

    p = D_00483748;
    if (p != 0) {
        goto live;
    }
    return 0;
live:
    return p->q->flags & 1;
}
