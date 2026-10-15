#include "types.h"

extern s32 ScriptSlotGetInt_3348b0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004826E0;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s16 m04;
};

s32 ScriptCmdEffectNodeSetField4_333a40(s32 p0)
{
    s32 r;

    r = ScriptSlotGetInt_3348b0(p0);
    D_004826E0->m04 = r;
    return 1;
}
