#include "types.h"

extern s32 GetMapMgr_201a90(void);
extern s32 ScriptGetCodeAddr_26a200(s32);
extern s32 MapSetSkyIdByName_1e4150(s32, s32);
extern void MapSetSlot2AreaIdByName_1e40c0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdSetSkyAndSlot2AreaByName_25fd90(s32 p0, s32 p1)
{
    s32 r0;
    s32 rv3;
    s32 r1;
    s32 r2;
    s32 r4;

    r0 = GetMapMgr_201a90();
    rv3 = r0;
    if (p1 > 0) {
        r1 = ScriptGetCodeAddr_26a200(p0);
        r2 = MapSetSkyIdByName_1e4150(r0, r1);
        rv3 = r2;
    }
    if (p1 > 1) {
        r4 = ScriptGetCodeAddr_26a200((p0 + 8));
        MapSetSlot2AreaIdByName_1e40c0(r0, r4);
    }
    return 1;
}
