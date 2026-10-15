#include "types.h"

extern s32 CaptionCfgInit_340240(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CaptionCfgCtor_3402e0(s32 p0)
{
    s32 r0;

    r0 = CaptionCfgInit_340240(p0, 0);
    return p0;
}
