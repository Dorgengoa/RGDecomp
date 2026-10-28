/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuSpecialList_4fc1f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004FC1F0 -- 1,420 bytes, 355 instructions, 49 calls, 16 conditional
 * branches, br/ins 0.045.  Chain 0x25,0x24,0x23,0x22,0x1C,0x1B,9,1 REVERSED is
 * the block layout 1,9,0x1B,0x1C,0x22,0x23,0x24,0x25, with three fall-through
 * pairs (0x1B->0x1C, 0x22->0x23, 0x24->0x25); in each pair the SECOND case's
 * test is the one that keeps its `beql`, the first is a plain `beq`.
 *
 * The width max at 0x004FC34C is the `$at` compare class ([[at-compare-class]]):
 * `slt $1, $2, $18` feeding `bnel`.  The natural `if (w >= maxw)` puts the
 * compare in a GPR; the operand-swapped `if (maxw <= w)` -- same predicate,
 * same instruction -- is what puts it in `$1`.  x_at.py flags this site.
 */

typedef struct Card {
    u8 pad00[0x18];
    s8 f18;                     /* +0x18 */
    u8 pad19[0x38 - 0x19];
    s8 f38;                     /* +0x38 */
    s8 f39;                     /* +0x39 */
} Card;

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    void *f87C;                 /* +0x087C */
    u8    pad880[0x4F90 - 0x880];
    u8    f4F90[0x2C];          /* +0x4F90 */
    u8    pad4FBC[0x5B28 - 0x4FBC];
    Card *f5B28;                /* +0x5B28 */
    u8    pad5B2C[0x5EF1 - 0x5B2C];
    u8    f5EF1;                /* +0x5EF1 */
} Ins;

extern u8 insect_D_00524020[];

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/*rgp*/
/*rgp*/

void insect_InsectBattleMenuSpecialList_4fc1f0(Ins *o)
{
    s32 x9C;
    s32 x98;
    s32 x94;
    s32 x90;
    s32 x8C;
    s32 x88;
    s32 x84;
    s32 x80;
    void *g;
    void *p17;
    Card *e;
    s32 *tp;
    s32 *tbl;
    s32 n;
    s32 i;
    s32 maxw;
    s32 j;
    s32 w;
    s32 dx;

    g = (u8 *)o + 0x5054;
    e = o->f5B28;
    p17 = (u8 *)o + 0x50E8;
    if (e != 0) {
        switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
        case 1:
            tbl = ((s32 *)insect_InsectAbilityTableCollect_51cef0(p17, e->f38, e->f39, e->f18, 1));
            n = insect_InsectAbilityTableGetMatchCount_51cee0(p17);
            i = 0;
            do {
                UiSetTextString_28f510(o->f878, 0x7584, 0, i);
                i++;
            } while (i < 5);
            maxw = 0x7C;
            j = 0;
            while (j < n) {
                UiSetTextPos_28f5d0(o->f878, 0x7584, 6, (j << 5) + 8, j);
                tp = tbl + j;
                UiSetTextString_28f510(o->f878, 0x7584, *tp, j);
                UiSetTextColor_290a40(o->f878, 0x7584, 0xFF7F7F7F, j);
                w = insect_InsectMsgTextWidth_512ab0((u8 *)o + 0x506C, *tp, 2) + 0x10;
                if (maxw <= w) {
                    maxw = w;
                }
                j++;
            }
            InsectUiSpriteListClear_393960(g, ((s32)UiFindWidget_290460(o->f878, 0x7584)), 5);
            InsectBattleMenuFrameLayoutMaybe_392250(g, ((s32)UiFindWidget_290460(o->f878, 0x7581)),
                        ((s32)UiFindWidget_290460(o->f878, 0x7584)),
                        ((s32)UiFindWidget_290460(o->f878, 0x7582)), n, 1, maxw, o->f5EF1);
            UiQuadSetByModeRelated_3934d0(g, ((s32)UiFindWidget_290460(o->f878, 0x7583)), maxw - 4, 0x20, 5,
                        o->f5EF1);
            dx = 0x70;
            if (o->f5EF1 == 1) {
                dx = -(maxw + 4);
            }
            insect_InsectCursorSetGetCell_511a40(o->f4F90, 4, &x9C, &x98);
            UiGetWidgetAbsPos_290fc0(o->f878, 0x7560, &x94, &x90);
            UiSetWidgetPos_290f60(o->f878, 0x7580, x94, x90 + (x98 << 5));
            UiMoveWidgetUniform_290f50(o->f878, 0x7580, x94 + dx, x90 + (x98 << 5), 0.5f, 0);
            insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00524020, 1);
            UiSetWidgetAlpha_2907a0(o->f878, 0x7580, 0.0f);
            UiFadeWidgetAlpha_290690(o->f878, 0x7580, 1.0f, 0.125f, -1.0f);
            UiSetWidgetVisible_290010(o->f878, 0x7580, 1, -1);
            insect_InsectBattleSetStep_50d7a0(o, 9, 2, -1);
            break;
        case 9:
            insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00524020, 1);
            if (UiWidgetIsMoving_290d30(o->f878, 0x7580) == 0) {
                insect_InsectBattleSetStep_50d7a0(o, 0x1C, 2, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
            }
            break;
        case 0x1B:
            insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00524020, 1);
            UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
            insect_InsectBattleSetStep_50d7a0(o, 0x1C, 2, -1);
            /* fallthrough */
        case 0x1C:
            insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00524020, 0);
            break;
        case 0x22:
            insect_InsectCursorSetGetCell_511a40(o->f4F90, 4, &x8C, &x88);
            UiFadeWidgetAlpha_290690(o->f878, 0x7580, 0.0f, 0.125f, -1.0f);
            UiGetWidgetAbsPos_290fc0(o->f878, 0x7560, &x84, &x80);
            UiMoveWidgetUniform_290f50(o->f878, 0x7580, x84, x80 + (x88 << 5), 0.5f, 0);
            insect_InsectBattleSetStep_50d7a0(o, 0x23, 2, -1);
            /* fallthrough */
        case 0x23:
            insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00524020, 1);
            if (UiWidgetIsMoving_290d30(o->f878, 0x7580) == 0) {
                insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0x22, 0, -1);
            }
            break;
        case 0x24:
            UiFadeWidgetAlpha_290690(o->f878, 0x7580, 0.0f, 0.125f, -1.0f);
            UiFadeWidgetAlpha_290690(o->f878, 0x755F, 0.0f, 0.125f, -1.0f);
            UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
            insect_InsectBattleSetStep_50d7a0(o, 0x25, 2, -1);
            /* fallthrough */
        case 0x25:
            if (UiGetWidgetAlpha_290770(o->f878, 0x7580) <= 0.0f) {
                insect_InsectBattleSetStep_50d7a0(o, 0x24, 0, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
            }
            break;
        }
    }
}
