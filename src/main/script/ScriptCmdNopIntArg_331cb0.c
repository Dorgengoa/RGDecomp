#include "types.h"

extern s32 ScriptSlotGetInt_3348b0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 ScriptCmdNopIntArg_331cb0(s32 p0, s32 p1)
{
    s32 rv1;
    s32 r0;

    rv1 = 1;
    if (p1 != 2) {
        rv1 = 0;
    } else {
        r0 = ScriptSlotGetInt_3348b0(p0);
        rv1 = 1;
    }
    return rv1;
}
