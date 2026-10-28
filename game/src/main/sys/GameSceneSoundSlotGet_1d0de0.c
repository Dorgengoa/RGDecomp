/* rgp:protos */
#define RGP_SELF_GameSceneSoundSlotGet_1d0de0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Asymmetric guard pair whose index arrives as an s8 -- retail's leading
   `dsll32 24 / dsra32 24` is the sign extension of a char parameter, and both
   the negative guard and the bound then test the widened value.  Records are
   0x88 bytes at +0xB0B0, which is too far for an addiu, so mwcc materialises
   the displacement with `ori $at`. */

typedef struct OwnerB0B0 {
    u8 pad000[0xB0B0];
    u8 rec[1];         /* +0xB0B0, 0x88 bytes each */
} OwnerB0B0;

void *GameSceneSoundSlotGet_1d0de0(OwnerB0B0 *o, s8 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 7;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &o->rec[index * 0x88];
}
