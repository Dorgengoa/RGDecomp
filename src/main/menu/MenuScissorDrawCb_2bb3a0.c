#include "types.h"

extern s32 GsPktSetScissor_28c2e0(s32, void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047ED00;

s32 MenuScissorDrawCb_2bb3a0(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    s32 r0;

    r0 = GsPktSetScissor_28c2e0(p0, &D_0047ED00, p4, 0);
    return 1;
}
