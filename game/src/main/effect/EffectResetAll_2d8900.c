/* rgp:protos */
#define RGP_SELF_EffectResetAll_2d8900 1
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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004E0DD0[];
extern u8 D_004E34D0[];
extern u8 D_004E39D0[];
extern u8 D_004E3A90[];
extern u8 D_004E4190[];

void EffectResetAll_2d8900(void)
{
    s32 l0;
    s32 l2;
    s32 l4;
    s32 l6;
    s32 l8;
    s32 r10;
    s32 r12;
    s32 r14;
    s32 r16;
    s32 r19;

    l0 = 0;
    do {
        GuardEffectDeactivate_2d5060((D_004E0DD0 + (((l0 * 0xC) + l0) << 6)));
        l0 = (l0 + 1);
    } while (l0 < 0xC);
    l2 = 0;
    do {
        GuardWaveEffectReset_2d5660((D_004E34D0 + (l2 * 0x50)));
        l2 = (l2 + 1);
    } while (l2 < 0x10);
    l4 = 0;
    do {
        EffectTimedSlotReset_2d4cf0((D_004E39D0 + (l4 << 4)));
        l4 = (l4 + 1);
    } while (l4 < 0xC);
    l6 = 0;
    do {
        BladeLineReset_2d5b80((D_004E3A90 + (l6 * 0x70)));
        l6 = (l6 + 1);
    } while (l6 < 0x10);
    l8 = 0;
    do {
        MovingLineReset_2d5f30((D_004E4190 + (((l8 * 0x1C) - (l8 * 0x7)) << 4)));
        l8 = (l8 + 1);
    } while (l8 < 0x18);
    r10 = ((s32)GetEffectMgr_2d9040());
    EffectMgrUnlinkActive_2e1550(r10);
    r12 = ((s32)GetGameData_1fede0());
    GameDataStatusFxStopAll_3e6710(r12);
    r14 = ((s32)GetObjRefTable_313de0());
    HandleRegistryClear_314790(r14, 0, 0, 0);
    r16 = ((s32)GetActionMgr_1fdb50());
    ActionMgrEffectClearAll_2335a0(r16);
    ActionMgrStopSwordTrails_231680(r16);
    r19 = ((s32)GetBattleEffectPool_2d9030());
    BattleEffectPoolReset_2d3e90(r19);
}
