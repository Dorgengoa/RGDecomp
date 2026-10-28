/* rgp:protos */
#define RGP_SELF_EffectSpawnHitBullet_2d7eb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004616A0[0x400];

void EffectSpawnHitBullet_2d7eb0(s32 arg0, s32 arg1)
{
    u8 sp40[0x20] __attribute__((aligned(16)));
    s32 temp_2;

    temp_2 = ((s32)GetEffectMgr_2d9040());
    EffectReleaseByNameKey_2e0e50(temp_2, &(*(u8 *)D_004616A0), arg0);
    EffectCreateByName_2e1020(sp40, temp_2, &(*(u8 *)D_004616A0), -1);
    EffectSetId_2e0100(temp_2, sp40, arg0);
    EffectSetPos_2e0bb0(temp_2, sp40, arg1);
    EffectSetParamInt_2e0530(temp_2, sp40, 0, 1);
    EffectStep_2e0e00(temp_2, sp40);
}
