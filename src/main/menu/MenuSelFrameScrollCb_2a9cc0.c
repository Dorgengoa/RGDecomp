#include "types.h"

extern s32 UiSelFrameAnimStep_28d820(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004DB430[];

s32 MenuSelFrameScrollCb_2a9cc0(void)
{
    s32 r;

    r = UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
