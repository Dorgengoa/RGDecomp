/* rgp:protos */
#define RGP_SELF_EvSwitchObjGetStateRec_2f8410 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Asymmetric guard pair returning the address of a 0x24-byte record; 2 of
   them at +0x110. */

typedef struct Owner_FUN_002f8410 {
    u8 pad000[0x110];
    u8 rec[1];         /* +0x110, 0x24 bytes each */
} Owner_FUN_002f8410;

void *EvSwitchObjGetStateRec_2f8410(Owner_FUN_002f8410 *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 2;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &o->rec[index * 0x24];
}
