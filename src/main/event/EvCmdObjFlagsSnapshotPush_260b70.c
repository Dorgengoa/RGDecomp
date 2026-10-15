#include "types.h"

extern s32 GetObjRecFlagsSnapshotStack_1d7640(void);
extern s32 ObjRecFlagsSnapshotPush_1d77a0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481F78;

s32 EvCmdObjFlagsSnapshotPush_260b70(void)
{
    s32 r0;
    s32 r1;

    r0 = GetObjRecFlagsSnapshotStack_1d7640();
    r1 = ObjRecFlagsSnapshotPush_1d77a0(r0, D_00481F78);
    return 1;
}
