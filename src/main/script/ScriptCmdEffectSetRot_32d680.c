#include "types.h"

extern void ScriptSlotsToVec4_334810(void *, s32);
extern s32 EffectInstanceSetRot_2dd560(s32, void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004826E0;

s32 ScriptCmdEffectSetRot_32d680(s32 p0, s32 p1)
{
    u128 v10;
    s32 rv2;
    s32 t0;
    s32 r1;

    rv2 = 1;
    if (p1 != 3) {
        rv2 = 0;
    } else {
        ScriptSlotsToVec4_334810(&v10, p0);
        t0 = D_004826E0;
        if (t0 != 0) {
            r1 = EffectInstanceSetRot_2dd560(t0, &v10);
        }
        rv2 = 1;
    }
    return rv2;
}
