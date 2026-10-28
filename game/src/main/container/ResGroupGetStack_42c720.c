/* rgp:protos */
#define RGP_SELF_ResGroupGetStack_42c720 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Asymmetric guard pair returning the address of a 0x58-byte record; 4 of
   them at +0x4. */

typedef struct Owner_FUN_0042c720 {
    u8 pad000[0x4];
    u8 rec[1];         /* +0x4, 0x58 bytes each */
} Owner_FUN_0042c720;

void *ResGroupGetStack_42c720(Owner_FUN_0042c720 *o, s32 index)
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
    return &o->rec[index * 0x58];
}
