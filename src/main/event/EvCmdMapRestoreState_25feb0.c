#include "types.h"

extern s32 GetMapMgr_201a90(void);
extern s32 MapRestoreState_1e41c0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdMapRestoreState_25feb0(void)
{
    s32 r0;
    s32 r1;

    r0 = GetMapMgr_201a90();
    r1 = MapRestoreState_1e41c0(r0);
    return 1;
}
