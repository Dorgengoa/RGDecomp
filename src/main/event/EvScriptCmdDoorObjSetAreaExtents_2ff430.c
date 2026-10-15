#include "types.h"

extern f32 ScriptArgGetFloat_301a20(s32);
extern s32 EvDoorObjSetAreaExtents_304050(void *, f32, f32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004E69D0[];

s32 EvScriptCmdDoorObjSetAreaExtents_2ff430(s32 p0, s32 p1)
{
    s32 rv4;
    f32 r0;
    f32 r1;
    f32 r2;
    s32 r3;

    rv4 = 1;
    if (p1 != 3) {
        rv4 = 0;
    } else {
        r0 = ScriptArgGetFloat_301a20(p0);
        r1 = ScriptArgGetFloat_301a20((p0 + 8));
        r2 = ScriptArgGetFloat_301a20((p0 + 0x10));
        r3 = EvDoorObjSetAreaExtents_304050(D_004E69D0, r0, r1, r2);
        rv4 = 1;
    }
    return rv4;
}
