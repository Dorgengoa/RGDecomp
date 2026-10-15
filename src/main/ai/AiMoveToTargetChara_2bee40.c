#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 AiGetTargetCharaId_2c0fd0(s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 AiSetTargetMissing_2c11d0(s32, s32);
extern s32 CharaGetPos_2388a0(s32, void *);
extern s32 AiRouteMoveToPosMaybe_2beed0(s32, s32, void *, s32);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 AiMoveToTargetChara_2bee40(s32 p0, s32 p1)
{
    u128 v40;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;

    r0 = GetActionMgr_1fdb50();
    r1 = AiGetTargetCharaId_2c0fd0(p0);
    r2 = ActionMgrFindById_233b50(r0, r1);
    if (r2 == 0) {
        r3 = AiSetTargetMissing_2c11d0(p0, 1);
        return r3;
    }
    r4 = CharaGetPos_2388a0(r2, &v40);
    r5 = AiRouteMoveToPosMaybe_2beed0(p0, p1, &v40, r2);
    return r5;
}
