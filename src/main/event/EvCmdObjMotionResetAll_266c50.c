#include "types.h"

extern s32 ScriptGetInt_26a2a0(s32);
extern s32 EventSceneGetObj_2676e0(s32);
extern s32 MotionListResetAll_171e00(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdObjMotionResetAll_266c50(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 rv3;
    s32 r2;

    r0 = ScriptGetInt_26a2a0(p0);
    r1 = EventSceneGetObj_2676e0(r0);
    rv3 = 1;
    if (r1 == 0) {
        rv3 = 0;
    } else {
        r2 = MotionListResetAll_171e00((r1 + 0x1F0));
        rv3 = 1;
    }
    return rv3;
}
