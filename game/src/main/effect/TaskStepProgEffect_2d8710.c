/* rgp:protos */
#define RGP_SELF_TaskStepProgEffect_2d8710 1
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
/*rgp*/
/*rgp*/
/*rgp*/

extern u8 D_004E0DD0[];
extern u8 D_004E34D0[];
extern u8 D_004E39D0[];
extern u8 D_004E3A90[];
extern u8 D_004E4190[];
extern u8 D_004E6110[];

void TaskStepProgEffect_2d8710(void)
{
    s32 r0;
    s32 r2;
    s32 l4;
    s32 l6;
    s32 l8;
    s32 l10;
    s32 l12;

    r0 = ((s32)GetBattleEffectPool_2d9030());
    BattleEffectPoolUpdate_2d3e30(r0);
    r2 = ((s32)GetDamagePopupList_2d9020());
    DamagePopupUpdateAll_2d30e0(r2);
    l4 = 0;
    do {
        GuardEffectStepMaybe_2d5260((D_004E0DD0 + (l4 * 0x340)));
        l4 = (l4 + 1);
    } while (l4 < 0xC);
    l6 = 0;
    do {
        GuardWaveEffectStepMaybe_2d56f0((D_004E34D0 + (l6 * 0x50)));
        l6 = (l6 + 1);
    } while (l6 < 0x10);
    l8 = 0;
    do {
        EffectTimedSlotTick_2d4c10((D_004E39D0 + (l8 << 4)), 1.0f);
        l8 = (l8 + 1);
    } while (l8 < 0xC);
    l10 = 0;
    do {
        BladeLineUpdate_2d5e50((D_004E3A90 + (((l10 << 3) - l10) << 4)));
        l10 = (l10 + 1);
    } while (l10 < 0x10);
    l12 = 0;
    do {
        MovingLineUpdate_2d6220((D_004E4190 + (((((l12 << 3) - l12) << 2) - ((l12 << 3) - l12)) << 4)));
        l12 = (l12 + 1);
    } while (l12 < 0x18);
    LightningMgrUpdate_2d6b30(D_004E6110);
}
