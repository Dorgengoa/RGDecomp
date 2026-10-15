#include "types.h"

extern s32 ScriptSlotGetInt_3348b0(s32);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectCopyHandle_2dd3b0(void *, s32);
extern s32 EffectSetAutoRelease_2e1170(s32, void *, s32);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004826E0;

s32 ScriptCmdEffectSetAutoRelease_32e310(s32 p0)
{
    u128 v30[2];
    s32 r0;
    s32 t0;
    s32 r1;
    s32 rv4;
    s32 t1;
    s32 r3;

    r0 = ScriptSlotGetInt_3348b0(p0);
    t0 = D_004826E0;
    if (t0 == 0) {
        return 0;
    }
    r1 = GetEffectMgr_2d9040();
    rv4 = 1;
    if (r1 == 0) {
        rv4 = 0;
    } else {
        t1 = D_004826E0;
        EffectCopyHandle_2dd3b0(v30, t1);
        r3 = EffectSetAutoRelease_2e1170(r1, v30, (r0 != 0));
        rv4 = 1;
    }
    return rv4;
}
