#include "types.h"

typedef struct E8W { u8 b[8]; } E8W;

extern void ScriptSlotGetInt_3348b0(s32);
extern void ScriptSlotsToVec4_334810(void *, s32);
extern void EffectInstanceSetRot_2dd560(s32, void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004826E0;

s32 ScriptCmdEffectSetRot_332200(s32 p0, s32 p1)
{
    u128 v20;
    s32 t0;
    E8W *q;

    q = (E8W *)p0;
    if (p1 != 4) {
        return 0;
    }
    ScriptSlotGetInt_3348b0((s32)q++);
    ScriptSlotsToVec4_334810(&v20, (s32)q);
    t0 = D_004826E0;
    if (t0 != 0) {
        EffectInstanceSetRot_2dd560(t0, &v20);
    }
    return 1;
}
