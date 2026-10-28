/* rgp:protos */
#define RGP_SELF_BattleEffectBurstInit_2d3f30 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

void BattleEffectBurstInit_2d3f30(struct Obj0 *p0)
{
    s32 l0;
    s32 l1;

    p0->m00 = 0;
    l1 = 0;
    do {
        *(u8 *)((u8 *)p0 + (l1 << 6) + 0x54) = 0;
        l0 = ((l1 + 1) < 0x40);
        l1 = (l1 + 1);
    } while (l0 != 0);
}
