#include "types.h"

extern s32 GetMapMgr_201a90(void);
extern void MapMgrGetAuxArea_1e56d0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapMgrGetAuxAreaFwd_389e40(void)
{
    s32 r0;

    r0 = GetMapMgr_201a90();
    MapMgrGetAuxArea_1e56d0(r0);
}
