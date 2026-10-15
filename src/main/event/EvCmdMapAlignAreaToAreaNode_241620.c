#include "types.h"

extern s32 GetMapMgr_201a90(void);
extern s32 ScriptGetCodeAddr_249050(s32);
extern s32 MapAlignAreaToAreaNode_1e3fb0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdMapAlignAreaToAreaNode_241620(s32 p0, s32 p1)
{
    s32 rv3;
    s32 r0;
    s32 r1;
    s32 r2;

    rv3 = 1;
    if (p1 != 1) {
        rv3 = 0;
    } else {
        r0 = GetMapMgr_201a90();
        r1 = ScriptGetCodeAddr_249050(p0);
        r2 = MapAlignAreaToAreaNode_1e3fb0(r0, r1);
        rv3 = 1;
    }
    return rv3;
}
