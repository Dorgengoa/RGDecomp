#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern s32 ScriptGetInt_2490f0(s32);
extern s32 GameSceneSoundSlot5PlaySe_1d05a0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdSceneSePlaySlot5_2407d0(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = GetCurrentScene_1f5be0();
    r1 = ScriptGetInt_2490f0(p0);
    r2 = GameSceneSoundSlot5PlaySe_1d05a0(r0, r1);
    return 1;
}
