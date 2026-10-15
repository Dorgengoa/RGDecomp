#include "types.h"

extern s32 ScriptGetInt_26a2a0(s32);
extern s32 EvtGetSubMachine_26abb0(s32);
extern s32 EventSubNodeAddWaitMotionEnd_251250(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdSubWaitMotionEnd_262e70(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 rv3;
    s32 r2;

    r0 = ScriptGetInt_26a2a0(p0);
    r1 = EvtGetSubMachine_26abb0(r0);
    rv3 = 1;
    if (r1 == 0) {
        rv3 = 0;
    } else {
        r2 = EventSubNodeAddWaitMotionEnd_251250(r1);
        rv3 = 1;
    }
    return rv3;
}
