/* rgp:protos */
#define RGP_SELF_EffectResAllocSlot_2e2e10 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
};

s32 EffectResAllocSlot_2e2e10(s32 p0, struct Obj0 *p1)
{
    s32 l0;
    s32 t0;

    l0 = 0;
    while (l0 < 0x30) {
        t0 = *(s32 *)((u8 *)p0 + (((l0 << 3) - l0) << 4) + 0x174);
        if (t0 == -1) {
            p1->m00 = l0;
            return ((p0 + (((l0 << 3) - l0) << 4)) + 0x174);
        }
        l0 = (l0 + 1);
    }
    return 0;
}
