/* rgp:protos */
#define RGP_SELF_MenuWeaponCombineSetHandles_3636a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x83];
    u8 m83;
    s32 m84;
    s32 m88;
    s32 m8C;
    s32 m90;
};

void MenuWeaponCombineSetHandles_3636a0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    p0->m84 = p1;
    p0->m88 = p2;
    p0->m8C = p3;
    p0->m90 = p4;
    p0->m83 = 0;
}
