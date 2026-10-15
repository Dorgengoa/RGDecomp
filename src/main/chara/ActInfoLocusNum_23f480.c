#include "types.h"

extern s32 ScriptArgGetInt_23fc00(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s16 D_004BCE9A;

s32 ActInfoLocusNum_23f480(s32 p0, s32 p1)
{
    s32 rv1;
    s32 r0;

    rv1 = 1;
    if (p1 != 1) {
        rv1 = 0;
    } else {
        r0 = ScriptArgGetInt_23fc00(p0);
        *(s16 *)&D_004BCE9A = r0;
        rv1 = 1;
    }
    return rv1;
}
