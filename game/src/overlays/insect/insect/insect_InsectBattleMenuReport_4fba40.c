/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuReport_4fba40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004FBA40 -- 628 bytes, 157 instructions, 22 calls, 6 conditional
 * branches, br/ins 0.038.  The 0x7585-0x7588 panel builder on the
 * insect_InsectBattleGetStep_50d6a0(o, 2) state.
 *
 * Compare chain 3, 0x1D, 1 -- REVERSED -- so source order is 1, 0x1D, 3, which
 * is the block order (0x4FBA94, 0x4FBC24, 0x4FBC58).  Case 0x1D FALLS THROUGH
 * into case 3: its last instruction (`lw $4, 0x878($18)` at 0x4FBC54) is case
 * 3's first argument load, hoisted, and there is no `b` between them.
 *
 * insect_D_00525FF0 is REMATERIALISED with its own `lui`/`addiu` at every one of its
 * nine sites, so it stays a plain extern reference -- the opposite of the same
 * family's 0x0050EAF0, where retail hoists the identical kind of handle into a
 * callee-saved register and the source needs a local.  Read which one retail
 * did off the listing; it is not a property of the callee.
 *
 * Both `(o->f5DA0 - 0x1B8) / 2` divides are written out as `bgez / addiu 1 /
 * sra 1`, the SIGNED divide-by-two, so the source really divides.
 */

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    u8    pad87C[0x506C - 0x87C];
    u8    f506C[4];             /* +0x506C */
    u8    pad5070[0x5DA0 - 0x5070];
    s32   f5DA0;                /* +0x5DA0 */
    s32   f5DA4;                /* +0x5DA4 */
    u8    pad5DA8[0x5EF1 - 0x5DA8];
    u8    f5EF1;                /* +0x5EF1 */
} Ins;

extern u8 insect_D_00525FF0[];

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

void insect_InsectBattleMenuReport_4fba40(Ins *o)
{
    void *p;
    void *g;

    p = (u8 *)o + 0x506C;
    g = (u8 *)o + 0x5054;
    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        InsectBattleMenuFrameNineSliceMaybe_393ac0(g, UiFindWidget_290460(insect_D_00525FF0, 0x7586), 0x1B8, 0x124, 0);
        UiSpriteListFillColumnMaybe_3939e0(g, UiFindWidget_290460(insect_D_00525FF0, 0x7588), 1, 0, 432.0f, 288.0f);
        UiQuadSetByModeRelated_3934d0(g, UiFindWidget_290460(insect_D_00525FF0, 0x7587), 0x1B0, 0x11C, 1,
                    o->f5EF1);
        UiSetWidgetVisible_290010(insect_D_00525FF0, 0x7585, 1, -1);
        UiSetWidgetPos_290f60(insect_D_00525FF0, 0x7586, (o->f5DA0 - 0x1B8) / 2,
                    (o->f5DA4 - 0x124) / 2);
        UiSetWidgetAlpha_2907a0(insect_D_00525FF0, 0x7586, 0.0f);
        UiFadeWidgetAlpha_290690(insect_D_00525FF0, 0x7586, 1.0f, 0.125f, -1.0f);
        UiSetWidgetPos_290f60(o->f878, 0x7588, 0, 0x20);
        UiSetTextString_28f510(o->f878, 0x7586, ((s32)insect_InsectMsgGet_512b70(p, 0x27)), 0);
        UiSetWidgetPos_290f60(o->f878, 0x7587, 4, 4);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
        break;
    case 0x1D:
        UiFadeWidgetAlpha_290690(o->f878, 0x7586, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 3, 2, -1);
        /* fallthrough */
    case 3:
        if (UiGetWidgetAlpha_290770(o->f878, 0x7586) <= 0.0f) {
            insect_InsectBattleSetState_50d8c0(o, 0x28, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
        }
        break;
    }
}
