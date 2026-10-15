#include "types.h"

extern s32 PadGetTriggeredMask_183d00(void *);
extern s32 ScriptSetRefInt_249030(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004B2570[];

s32 EvCmdPadGetTriggered_2420b0(s32 p0, s32 p1)
{
    s32 rv2;
    s32 r0;
    s32 r1;

    rv2 = 1;
    if (p1 <= 0) {
        rv2 = 0;
    } else {
        r0 = PadGetTriggeredMask_183d00(D_004B2570);
        r1 = ScriptSetRefInt_249030(p0, r0);
        rv2 = 1;
    }
    return rv2;
}
