#include "types.h"

extern s32 ScriptGetInt_2490f0(s32);
extern void SetPendingFadeFrames_27bd50(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdSetPendingFade_2406c0(s32 p0)
{
    s32 r0;
    s32 rv1;
    s32 rv2;
    s32 rv3;

    r0 = ScriptGetInt_2490f0(p0);
    rv1 = r0;
    if (r0 == -1) {
        rv1 = 0x28;
    }
    rv2 = rv1;
    rv3 = rv1;
    if (rv1 == -2) {
        rv2 = 0x14;
        rv3 = 0x14;
    }
    SetPendingFadeFrames_27bd50(rv3);
    return 1;
}
