#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern void ScreenFadeDraw_1cf6d0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void TaskDrawFade_2f6e60(void)
{
    s32 r0;

    r0 = GetCurrentScene_1f5be0();
    ScreenFadeDraw_1cf6d0(r0);
}
