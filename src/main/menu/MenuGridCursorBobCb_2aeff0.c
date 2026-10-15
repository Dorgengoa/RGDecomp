#include "types.h"

extern void MenuCursorBobToCell_2b0170(s32, s32, s32);
extern s32 UiSelFrameAnimStep_28d820(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004DB430[];

s32 MenuGridCursorBobCb_2aeff0(s32 p0)
{
    s32 r1;

    MenuCursorBobToCell_2b0170(p0, 0x62, 0x49);
    r1 = UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
