#include "types.h"

extern s32 GetEffectMgr_2d9040(void);
extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern s32 EffectReleaseNodesByKey_2e1250(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 AiCmdEffectReleaseByKey_2c1ed0(s32 p0, s32 p1)
{
    s32 rv3;
    s32 r0;
    s32 r1;
    s32 r2;

    rv3 = 1;
    if (p1 <= 0) {
        rv3 = 0;
    } else {
        r0 = GetEffectMgr_2d9040();
        r1 = ScriptSlotGetInt_2cc9c0(p0);
        r2 = EffectReleaseNodesByKey_2e1250(r0, r1, 0x1B58);
        rv3 = 1;
    }
    return rv3;
}
