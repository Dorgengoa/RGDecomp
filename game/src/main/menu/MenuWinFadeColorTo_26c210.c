/* rgp:protos */
#define RGP_SELF_MenuWinFadeColorTo_26c210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

struct Obj0;
struct Obj1;

struct Obj0 {
    u128 m00;
};

struct Obj1 {
    u8 pad000[0xA0];
    u128 mA0;
    u8 pad0B0[0x4];
    s32 mB4;
};

void MenuWinFadeColorTo_26c210(struct Obj1 *p0, struct Obj0 *p1, s32 p2)
{
    p0->mA0 = p1->m00;
    p0->mB4 = p2;
}
