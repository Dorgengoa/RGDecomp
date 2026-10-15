#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const f32 D_0045B078;

struct Obj0;

struct Obj0 {
    u8 pad000[0x40E];
    s16 m40E;
    s16 m410;
};

void CharaArmCollIgnoreTimer_238500(struct Obj0 *p0)
{
    f32 t0;
    s16 t1;

    t0 = D_0045B078;
    p0->m410 = ((s32)(0.5f * t0));
    t1 = p0->m40E;
    p0->m40E = (t1 | 0x1000);
}
