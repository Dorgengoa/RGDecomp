/* rgp:protos */
#define RGP_SELF_TaskDrawProgEffect_2d85d0 1
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

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004E0DD0[];
extern u8 D_004E34D0[];
extern u8 D_004E39D0[];
extern u8 D_004E3A90[];
extern u8 D_004E4190[];
extern u8 D_004E6110[];

void TaskDrawProgEffect_2d85d0(void)
{
    s32 r0;
    s32 l2;
    s32 l4;
    s32 l6;
    s32 l8;
    s32 l10;
    s32 r13;

    r0 = ((s32)GetBattleEffectPool_2d9030());
    BattleEffectPoolDraw_2d3db0(r0);
    l2 = 0;
    do {
        GuardEffectDraw_2d50b0((D_004E0DD0 + (((l2 * 0xC) + l2) << 6)));
        l2 = (l2 + 1);
    } while (l2 < 0xC);
    l4 = 0;
    do {
        GuardWaveEffectDraw_2d5830((D_004E34D0 + (l4 * 0x50)));
        l4 = (l4 + 1);
    } while (l4 < 0x10);
    l6 = 0;
    do {
        EffectTimedSlotDrawMaybe_2d4950((D_004E39D0 + (l6 << 4)));
        l6 = (l6 + 1);
    } while (l6 < 0xC);
    l8 = 0;
    do {
        BladeLineDraw_2d5c40((D_004E3A90 + (l8 * 0x70)));
        l8 = (l8 + 1);
    } while (l8 < 0x10);
    l10 = 0;
    do {
        MovingLineDraw_2d5ff0((D_004E4190 + (((l10 * 0x1C) - (l10 * 0x7)) << 4)));
        l10 = (l10 + 1);
    } while (l10 < 0x18);
    LightningMgrDrawThunk_2d7180(D_004E6110);
    r13 = ((s32)GetActionMgr_1fdb50());
    ActionMgrDrawSwordTrails_231630(r13);
}
