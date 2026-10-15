#include "types.h"

extern s32 ScriptGetInt_2490f0(s32);
extern s32 GetMapMgr_201a90(void);
extern s32 MapMgrCaptionLoad_1e2f10(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdMapCaptionLoad_2442e0(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = ScriptGetInt_2490f0(p0);
    r1 = GetMapMgr_201a90();
    r2 = MapMgrCaptionLoad_1e2f10(r1, r0, 0);
    return 1;
}
