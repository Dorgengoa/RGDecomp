#include "types.h"

extern s32 MapFindAreaSlotById_1e4cb0(s32, s32);
extern s32 MapScriptCall_1e99d0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapAreaCallScriptById_1e43b0(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;

    r0 = MapFindAreaSlotById_1e4cb0(p0, p1);
    if (r0 != 0) {
        r1 = MapScriptCall_1e99d0(r0, p2);
        return r1;
    }
    return -1;
}
