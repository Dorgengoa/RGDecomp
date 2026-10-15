#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_0047D2AC;

struct Obj0;

struct Obj0 {
    u8 pad000[0x48];
    f32 m48;
    s32 m4C;
};

void MenuFadeStartFromColor_2a0020(struct Obj0 *p0)
{
    p0->m48 = D_0047D2AC;
    p0->m4C = 0x3F800000;
}
