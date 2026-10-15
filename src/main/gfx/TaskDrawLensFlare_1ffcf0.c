#include "types.h"

extern s32 GetLensFlareMgr_201a40(void);
extern void LensFlareDraw_2ed830(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void TaskDrawLensFlare_1ffcf0(void)
{
    s32 r0;

    r0 = GetLensFlareMgr_201a40();
    LensFlareDraw_2ed830(r0);
}
