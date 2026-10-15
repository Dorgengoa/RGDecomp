#include "types.h"

extern s32 ScriptGetInt_26a2a0(s32);
extern void SceneObjsSetTimerA7CRelated_1f9380(s32);
extern s32 MonographDrawHoldSetFrames_2d1940(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdSceneObjsSetTimerMaybe_259aa0(s32 p0)
{
    s32 r0;
    s32 r2;

    r0 = ScriptGetInt_26a2a0(p0);
    SceneObjsSetTimerA7CRelated_1f9380(r0);
    r2 = MonographDrawHoldSetFrames_2d1940(r0);
    return 1;
}
