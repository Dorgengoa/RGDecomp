#include "types.h"

extern s32 GetPauseStep_2f6660(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482770;
extern u8 D_00482778;

s32 PauseRequest_2f65e0(s32 p0)
{
    s32 r0;

    r0 = GetPauseStep_2f6660();
    if (r0 == 0) {
        D_00482770 = p0;
        D_00482778 = 1;
    }
    return r0;
}
