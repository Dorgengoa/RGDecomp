#include "types.h"

extern s32 ScriptGetInt_26a2a0(s32);
extern void HatenaMarkStepAll_345d60(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdHatenaMarkStepN_2591e0(s32 p0, s32 p1)
{
    s32 rv1;
    s32 r0;
    s32 l2;

    rv1 = 1;
    if (p1 > 0) {
        r0 = ScriptGetInt_26a2a0(p0);
        rv1 = r0;
    }
    l2 = 0;
    while (l2 < rv1) {
        HatenaMarkStepAll_345d60();
        l2 = (l2 + 1);
    }
    return 1;
}
