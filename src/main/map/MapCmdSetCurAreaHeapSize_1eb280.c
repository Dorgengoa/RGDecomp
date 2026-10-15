#include "types.h"

extern s32 ScriptArgGetInt_1ecbe0(s32);
extern s32 MapDataSetHeapSize_1e7470(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004818FC;

s32 MapCmdSetCurAreaHeapSize_1eb280(s32 p0, s32 p1)
{
    s32 t0;
    s32 r0;
    s32 t1;
    s32 r1;

    if (p1 != 1) {
        return 0;
    }
    t0 = D_004818FC;
    if (t0 == 0) {
        return 1;
    }
    r0 = ScriptArgGetInt_1ecbe0(p0);
    t1 = D_004818FC;
    r1 = MapDataSetHeapSize_1e7470(t1, r0);
    return 1;
}
