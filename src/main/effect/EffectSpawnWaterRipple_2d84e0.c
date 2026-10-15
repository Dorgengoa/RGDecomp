#include "types.h"

extern s32 GetEffectMgr_2d9040(void);
extern void EffectSetId_2e0100(s32 arg0, void *arg1, s32 arg2);
extern void EffectSetParamInt_2e0530(s32 arg0, void *arg1, s32 arg2, s32 arg3);
extern void EffectSetParamFloat_2e0600(s32 arg0, void *arg1, s32 arg2, f32 arg3);
extern void EffectSetPos_2e0bb0(s32 arg0, void *arg1, s32 arg2);
extern void EffectCreateByName_2e1020(void *arg0, s32 arg1, void *arg2, s32 arg3);
extern u8 D_004616F8[];

void EffectSpawnWaterRipple_2d84e0(s32 arg0, s32 arg1)
{
    u8 sp40[0x20];
    s32 temp_2;

    temp_2 = GetEffectMgr_2d9040();
    EffectCreateByName_2e1020(sp40, temp_2, D_004616F8, -1);
    EffectSetPos_2e0bb0(temp_2, sp40, arg1);
    EffectSetId_2e0100(temp_2, sp40, arg0);
    EffectSetParamFloat_2e0600(temp_2, sp40, 0, 0.0f);
    EffectSetParamFloat_2e0600(temp_2, sp40, 1, 0.0f);
    EffectSetParamFloat_2e0600(temp_2, sp40, 2, 0.0f);
    EffectSetParamInt_2e0530(temp_2, sp40, 0, 0);
}
