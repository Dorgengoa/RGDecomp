#include "types.h"

extern s32 ActionResultSumDamage_3a6d20(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
};

s32 QueryActionResultSumDamage_3e3e60(struct Obj0 *p0)
{
    s32 t0;
    s32 r0;

    t0 = p0->m08;
    if (t0 != 0) {
        r0 = ActionResultSumDamage_3a6d20(t0);
        return r0;
    }
    return 0;
}
