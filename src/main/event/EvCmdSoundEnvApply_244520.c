#include "types.h"

extern s32 ScriptGetInt_2490f0(s32);
extern s32 GameSceneSoundEnvApplyPreset_1d0e30(s32, s32, s32, s32);
extern s32 GameSceneSoundSetPollHold_1d1180(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * gEventContext;

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 EvCmdSoundEnvApply_244520(s32 p0, s32 p1)
{
    s32 rv3;
    s32 r0;
    struct Obj0 * t0;
    s32 t1;
    s32 r1;
    struct Obj0 * t2;
    s32 t3;
    s32 r2;

    rv3 = 1;
    if (p1 != 1) {
        rv3 = 0;
    } else {
        r0 = ScriptGetInt_2490f0(p0);
        t0 = gEventContext;
        t1 = gEventContext->m00;
        r1 = GameSceneSoundEnvApplyPreset_1d0e30(t1, r0, 1, 0);
        t2 = gEventContext;
        t3 = gEventContext->m00;
        r2 = GameSceneSoundSetPollHold_1d1180(t3, 1);
        rv3 = 1;
    }
    return rv3;
}
