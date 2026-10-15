#include "types.h"

extern s32 GsPktSetScissorDefault_28c2d0(s32, void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004DB740[];

s32 MenuScissorDrawCb_2bb490(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    s32 r;

    r = GsPktSetScissorDefault_28c2d0(p0, D_004DB740, p4);
    return 1;
}
