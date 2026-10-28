/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuSpecialTargetSelectMaybe_4fc080 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004FC080 -- 364 bytes, 91 instructions, 13 calls, 4 conditional
 * branches, br/ins 0.044.  A three-arm `insect_InsectBattleGetStep_50d6a0(o, 2)` state
 * dispatch from x_band.py's branch-light band.
 *
 * The compare chain runs 0x23, 0x22, 1 -- REVERSED -- so the source case order
 * is 1, 0x22, 0x23, and the three blocks are laid out in exactly that order.
 * Case 0x22 FALLS THROUGH into case 0x23: there is no `b` between the last
 * insect_InsectBattleSetStep_50d7a0 of one and the `lui %hi(insect_D_00524050)` of the other, and
 * case 0x23's own test is a plain `beq` (not `beql`) because its block head is
 * also the fall-through target.
 *
 * `lwc1 $f1, -0x7EF8($28)` is main-image small data: _gp is 0x00485170, so the
 * symbol is D_0047D278, and it must stay a non-const `f32` extern to keep the
 * %gp_rel relocation (insect_InsectBattleParamWindowLayout_4f3620 spells it the same way).
 *
 * `c.lt.s $f0, $f1` + `bc1t` past the block is `>=` with the body as the
 * FALL-THROUGH, the polarity insect_InsectBattleMenuEndTurn_4fda60's case 3/4 pair records.
 */

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                     /* +0x0878 */
    void *f87C;                     /* +0x087C */
} Ins;

extern u8  insect_D_00524050[];
extern f32 D_0047D278;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleMenuSpecialTargetSelectMaybe_4fc080(Ins *o)
{
    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
        return;
    case 0x22:
        UiFadeWidgetAlpha_290690(o->f878, 0x7580, 1.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f878, 0x755F, 1.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 0x23, 2, -1);
        /* falls through */
    case 0x23:
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00524050, 1);
        if (UiGetWidgetAlpha_290770(o->f878, 0x7580) >= D_0047D278) {
            insect_InsectBattlePopState_50d880(o, 0);
            insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
            insect_InsectBattlePopState_50d880(o, 2);
            insect_InsectBattleSetStep_50d7a0(o, 0x1B, 2, -1);
        }
        return;
    }
}
