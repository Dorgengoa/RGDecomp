#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetMapMgr_201a90(void);
extern void MapMgrSlotsShowObjs_1e14f0(s32);
extern void GameSceneMapEffectDraw_1ced90(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void TaskDrawMapEffect_2f6da0(void)
{
    s32 r0;
    s32 r1;

    r0 = GetCurrentScene_1f5be0();
    r1 = GetMapMgr_201a90();
    MapMgrSlotsShowObjs_1e14f0(r1);
    GameSceneMapEffectDraw_1ced90(r0, 0x30D);
}
