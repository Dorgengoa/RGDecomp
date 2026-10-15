#include "types.h"

extern s32 PathLocalize_1c28c0(void *, s32);
extern s32 ResidentFileReadMaybe_1820a0(void *, s32, s32);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 ResidentFileReadLocalizedMaybe_1c2860(s32 p0, s32 p1, s32 p2)
{
    u128 v30[16];
    s32 r0;
    s32 rv2;
    s32 r1;

    r0 = PathLocalize_1c28c0(v30, p0);
    if ((r0 & 0xFF) == 0) {
        rv2 = 0;
    } else {
        r1 = ResidentFileReadMaybe_1820a0(v30, p1, p2);
        rv2 = (r1 != 0);
    }
    return rv2;
}
