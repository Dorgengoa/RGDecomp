#include "types.h"

extern s32 ScriptArgGetInt_23fc00(s32);
extern s32 CharaTableSetUseGauge_2253d0(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004BCDE0[];

s32 CharaTableValUseGauge_23c0d0(s32 p0, s32 p1)
{
    s32 rv2;
    s32 r0;
    s32 r1;

    rv2 = 1;
    if (p1 != 1) {
        rv2 = 0;
    } else {
        r0 = ScriptArgGetInt_23fc00(p0);
        r1 = CharaTableSetUseGauge_2253d0(D_004BCDE0, r0);
        rv2 = 1;
    }
    return rv2;
}
