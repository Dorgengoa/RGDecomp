#include "types.h"

extern s32 MenuCursorBobToCell_39c4d0(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MenuGridCursorBobCb_39c4a0(s32 p0, s32 p1)
{
    s32 r;

    r = MenuCursorBobToCell_39c4d0(p0, p1, -0x1A, 6);
    return 1;
}
