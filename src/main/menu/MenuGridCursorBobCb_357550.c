#include "types.h"

extern s32 MenuCursorBobUpdate_35b1b0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482380;

s32 MenuGridCursorBobCb_357550(void)
{
    s32 r;

    r = MenuCursorBobUpdate_35b1b0(D_00482380, 0);
    return 1;
}
