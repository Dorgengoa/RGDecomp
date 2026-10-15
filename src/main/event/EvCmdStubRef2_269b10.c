#include "types.h"

extern s32 ScriptSetRefInt_26a1e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdStubRef2_269b10(s32 p0, s32 p1)
{
    s32 rv1;
    s32 r0;

    rv1 = 1;
    if (p1 <= 0) {
        rv1 = 0;
    } else {
        r0 = ScriptSetRefInt_26a1e0(p0, 2);
        rv1 = 1;
    }
    return rv1;
}
