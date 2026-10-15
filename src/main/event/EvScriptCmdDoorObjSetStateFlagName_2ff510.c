#include "types.h"

extern s32 ScriptArgGetStr_301a00(s32);
extern s32 EventStrDup_301aa0(s32);
extern s32 EvDoorObjSetStateFlagName_303d80(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004E69D0[];

s32 EvScriptCmdDoorObjSetStateFlagName_2ff510(s32 p0, s32 p1)
{
    s32 rv3;
    s32 r0;
    s32 r1;
    s32 r2;

    rv3 = 1;
    if (p1 != 1) {
        rv3 = 0;
    } else {
        r0 = ScriptArgGetStr_301a00(p0);
        r1 = EventStrDup_301aa0(r0);
        r2 = EvDoorObjSetStateFlagName_303d80(D_004E69D0, r1);
        rv3 = 1;
    }
    return rv3;
}
