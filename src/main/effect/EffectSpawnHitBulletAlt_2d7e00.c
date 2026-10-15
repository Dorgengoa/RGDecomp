#include "types.h"

extern s32 GetEffectMgr_2d9040(void);
extern void EffectSetId_2e0100(s32, void *, s32);
extern void EffectSetParamInt_2e0530(s32, void *, s32, s32);
extern void EffectSetPos_2e0bb0(s32, void *, s32);
extern void EffectStep_2e0e00(s32, void *);
extern void EffectReleaseByNameKey_2e0e50(s32, void *, s32);
extern void EffectCreateByName_2e1020(void *, s32, void *, s32);
extern u8 D_004616A0[];

void EffectSpawnHitBulletAlt_2d7e00(s32 arg0, s32 arg1) {
    u8 sp40[0x20];
    s32 temp_2;

    temp_2 = GetEffectMgr_2d9040();
    EffectReleaseByNameKey_2e0e50(temp_2, D_004616A0, arg0);
    EffectCreateByName_2e1020(sp40, temp_2, D_004616A0, -1);
    EffectSetId_2e0100(temp_2, sp40, arg0);
    EffectSetPos_2e0bb0(temp_2, sp40, arg1);
    EffectSetParamInt_2e0530(temp_2, sp40, 0, 0);
    EffectStep_2e0e00(temp_2, sp40);
}
