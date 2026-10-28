/* rgp:protos */
#define RGP_SELF_GameRecGetCageSlot_3ce1f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Asymmetric guard pair returning the address of a 0x7F0-byte record; 3 of
   them at +0x30C. */

typedef struct Owner_FUN_003ce1f0 {
    u8 pad000[0x30C];
    u8 rec[1];         /* +0x30C, 0x7F0 bytes each */
} Owner_FUN_003ce1f0;

void *GameRecGetCageSlot_3ce1f0(Owner_FUN_003ce1f0 *o, s32 index)
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
    return &o->rec[index * 0x7F0];
}
