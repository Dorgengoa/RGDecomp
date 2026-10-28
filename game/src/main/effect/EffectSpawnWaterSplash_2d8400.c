/* rgp:protos */
#define RGP_SELF_EffectSpawnWaterSplash_2d8400 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004616E8[];

void EffectSpawnWaterSplash_2d8400(s32 arg0, s32 arg1) {
    u8 sp40[0x20] __attribute__((aligned(16)));
    s32 temp_2;

    temp_2 = ((s32)GetEffectMgr_2d9040());
    EffectCreateByName_2e1020(sp40, temp_2, D_004616E8, -1);
    EffectSetPos_2e0bb0(temp_2, sp40, arg1);
    EffectSetId_2e0100(temp_2, sp40, arg0);
    EffectSetParamFloat_2e0600(temp_2, sp40, 0, 0.0f);
    EffectSetParamFloat_2e0600(temp_2, sp40, 1, 0.0f);
    EffectSetParamFloat_2e0600(temp_2, sp40, 2, 0.0f);
    EffectSetParamInt_2e0530(temp_2, sp40, 0, 1);
    EffectSetParamInt_2e0530(temp_2, sp40, 1, 1);
}
