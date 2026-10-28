/* rgp:protos */
#define RGP_SELF_CharaGetEquipSlot_3ad420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Asymmetric guard pair returning the address of a 0x28-byte record; 0xA of
   them at +0x308. */

typedef struct Owner_FUN_003ad420 {
    u8 pad000[0x308];
    u8 rec[1];         /* +0x308, 0x28 bytes each */
} Owner_FUN_003ad420;

void *CharaGetEquipSlot_3ad420(Owner_FUN_003ad420 *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 0xA;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &o->rec[index * 0x28];
}
