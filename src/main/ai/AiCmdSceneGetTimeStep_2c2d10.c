#include "types.h"

extern f32 GameSceneGetTimeStep_1ceba0(s32);
extern s32 ScriptSlotStoreFloatRef_2cc8e0(s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_004DB920;

s32 AiCmdSceneGetTimeStep_2c2d10(s32 p0)
{
    s32 t0;
    f32 r0;
    s32 r1;

    t0 = D_004DB920;
    r0 = GameSceneGetTimeStep_1ceba0(t0);
    r1 = ScriptSlotStoreFloatRef_2cc8e0(p0, r0);
    return 1;
}
