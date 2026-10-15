#include "types.h"

extern s32 ScriptGetInt_26a2a0(s32);
extern s32 CharaReleaseAllById_2f2ed0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdCharaReleaseAll_2699d0(s32 p0, s32 p1)
{
    s32 rv2;
    s32 r0;
    s32 r1;

    rv2 = 1;
    if (p1 <= 0) {
        rv2 = 0;
    } else {
        r0 = ScriptGetInt_26a2a0(p0);
        r1 = CharaReleaseAllById_2f2ed0(r0);
        rv2 = 1;
    }
    return rv2;
}
