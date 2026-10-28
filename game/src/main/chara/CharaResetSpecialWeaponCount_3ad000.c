/* rgp:protos */
#define RGP_SELF_CharaResetSpecialWeaponCount_3ad000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00465D28;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4BC];
    u8 m4BC;
};

s32 CharaResetSpecialWeaponCount_3ad000(struct Obj0 *p0)
{
    p0->m4BC = D_00465D28;
    return 1;
}
