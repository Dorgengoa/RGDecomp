#include "types.h"

extern void ScriptSlotStoreIntRef_3347f0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004826E0;

struct Obj0;

struct Obj0 {
    u8 pad000[0x2];
    s16 m02;
};

s32 ScriptCmdEffectNodeGetIdMaybe_332850(s32 p0, s32 p1)
{
    struct Obj0 * t0;
    s16 t1;

    if (p1 <= 0) {
        return 0;
    }
    t0 = D_004826E0;
    if (t0 == 0) {
        ScriptSlotStoreIntRef_3347f0(p0, -1);
    } else {
        t1 = D_004826E0->m02;
        ScriptSlotStoreIntRef_3347f0(p0, t1);
    }
    return 1;
}
