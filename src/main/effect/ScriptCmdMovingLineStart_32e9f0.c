#include "types.h"

extern s32 ScriptSlotGetInt_3348b0(s32);
extern s32 MovingLineGet_2d8df0(s32);
extern s32 MovingLineStart_2d6420(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 ScriptCmdMovingLineStart_32e9f0(s32 p0, s32 p1)
{
    s32 rv3;
    s32 r0;
    s32 r1;
    s32 r2;

    rv3 = 1;
    if (p1 != 1) {
        rv3 = 0;
    } else {
        r0 = ScriptSlotGetInt_3348b0(p0);
        r1 = MovingLineGet_2d8df0(r0);
        if (r1 != 0) {
            r2 = MovingLineStart_2d6420(r1, 0x10);
        }
        rv3 = 1;
    }
    return rv3;
}
