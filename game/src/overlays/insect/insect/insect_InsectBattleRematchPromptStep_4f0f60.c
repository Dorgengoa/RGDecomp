/* rgp:protos */
#define RGP_SELF_insect_InsectBattleRematchPromptStep_4f0f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F0F60 -- 1,196 bytes, 299 instructions, 42 calls, 13 conditional
 * branches, br/ins 0.043.  A phase driver for the 0xC37x/0xC38F/0xC39x widget
 * set, dispatched through a real 6-entry jump table (insect_jtbl_00524BB0) on the s8
 * phase counter o->f5FC2.
 *
 * ★ THE TABLE IS BIASED: `addiu $2, $4, 0x1` before `sltiu $1, $2, 0x6`, so the
 * case set is -1..4, not 0..5 (insect-jump-table-density).  Case 2 FALLS
 * THROUGH into case 3, which is why the two blocks are adjacent; block order is
 * ascending, i.e. source order, so the reversed-compare-chain rule does not
 * apply here.  The range check's `beql` carries `lw $4, 0x87C($17)` -- the
 * shared tail's own first instruction -- so there is no `default:` arm.
 *
 * st is a named local because cases -1 and 2 REUSE the switch's own loaded
 * value (`addiu $2, $4, 0x1` with no `lb`), while cases 0, 1 and 3 re-read the
 * member because a call sits between.  Writing all five off the member gives
 * two extra loads; writing all five off `st` keeps it live across the calls.
 *
 * o->f4F90 and o->f506C are REMATERIALISED at every site (bare
 * `addiu $4, $17, K`) so they are array members; the 0x5054 and 0x5F82
 * addresses are both HOISTED into $16 and are locals --
 * insect-array-member-blocks-cse, both halves in one function.
 *
 * D_0047D88C is a gp float constant (_gp 0x00485170 - 0x78E4), so it must stay
 * NON-const to keep %gp_rel.
 */

typedef struct Ins {
    u8    pad000[0x87C];
    void *f87C;                 /* +0x087C */
    u8    pad880[0x4F90 - 0x880];
    u8    f4F90[0x2C];          /* +0x4F90 */
    u8    f4FBC;                /* +0x4FBC */
    u8    pad4FBD[0x506C - 0x4FBD];
    u8    f506C[4];             /* +0x506C */
    u8    pad5070[0x5DA0 - 0x5070];
    s32   f5DA0;                /* +0x5DA0 */
    s32   f5DA4;                /* +0x5DA4 */
    s32   f5DA8;                /* +0x5DA8 */
    u8    pad5DAC[0x5EF4 - 0x5DAC];
    s32   f5EF4;                /* +0x5EF4 */
    u8    pad5EF8[0x5FC2 - 0x5EF8];
    s8    f5FC2;                /* +0x5FC2 */
    s8    f5FC3;                /* +0x5FC3 */
    s8    f5FC4;                /* +0x5FC4 */
} Ins;

extern f32 D_0047D88C;
extern u8 insect_D_00524160[];
extern u8 insect_D_00524BA8[];

extern void  Sprintf_1343b8(void *p, s32 a, s32 b);
extern void  strcat(void *p, const u8 *t);
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
/*rgp*/
/*rgp*/

void insect_InsectBattleRematchPromptStep_4f0f60(Ins *o)
{
    s32 x4C;
    s32 x48;
    s32 v;
    void *g;
    void *p;
    s32 k;
    s32 n;
    s8  st;
    s8  t;
    s32 w;
    u8  b;
    u8  c;

    g = (u8 *)o + 0x5054;
    if (insect_InsectBattleTestFlag_50da40(o, 0x18) != 0) {
        st = o->f5FC2;
        switch (st) {
        case -1:
            o->f5FC2 = st + 1;
            break;
        case 0:
            insect_InsectBattleConfirmDialogOpen_50eaf0(o->f5DA0, o->f5DA4, o->f506C, 0x2B);
            o->f4FBC |= 0x10;
            o->f5FC2 = o->f5FC2 + 1;
            insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00524160, 1);
            if (insect_InsectBattleTestFlag_50da40(o, 0x3E) != 0 && o->f5DA8 == 4) {
                UiSetWidgetAlpha_2907a0(o->f87C, 0xC38F, 0.0f);
                UiFadeWidgetAlpha_290690(o->f87C, 0xC38F, 1.0f, 0.125f, -1.0f);
                UiWindowFrameLayoutMaybe_392bb0(g, UiFindWidget_290460(o->f87C, 0xC390), 0x140, 0x30, 0);
                InsectUiWindowFillSetSizeMaybe_3938f0(g, UiFindWidget_290460(o->f87C, 0xC391), 316.0f, 44.0f);
                p = (u8 *)o + 0x5F82;
                Sprintf_1343b8(p, ((s32)insect_InsectMsgGet_512b70(o->f506C, 0x2D)), o->f5EF4);
                if (insect_InsectBattleTestFlag_50da40(o, 0) != 0) {
                    strcat(p, insect_D_00524BA8);
                }
                UiSetTextString_28f510(o->f87C, 0xC390, p, 0);
                w = 0x140 - insect_InsectMsgTextWidth_512ab0(o->f506C, p, 2);
                UiSetTextPos_28f5d0(o->f87C, 0xC390, w / 2, 0x10, 0);
                UiSetWidgetVisible_290010(o->f87C, 0xC392, 0, -1);
                UiSetWidgetAlpha_2907a0(o->f87C, 0xC3A3, 0.0f);
            }
            break;
        case 1:
            UiFadeWidgetAlpha_290690(o->f87C, 0xC378, 1.0f, 0.125f, -1.0f);
            UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
            if (UiGetWidgetAlpha_290770(o->f87C, 0xC378) >= 1.0f) {
                o->f5FC2 = o->f5FC2 + 1;
            }
            break;
        case 2:
            o->f5FC2 = st + 1;
            o->f4FBC &= 0xFD;
            /* fallthrough */
        case 3:
            insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00524160, 0);
            insect_InsectCursorSetGetCurCell_511a90(o->f4F90, &x4C, &x48);
            InsectUiConfirmButtonSetSelectedMaybe_392b20(g, UiFindWidget_290460(o->f87C, 0xC37B), (u8)!(x4C != 0));
            InsectUiConfirmButtonSetSelectedMaybe_392b20(g, UiFindWidget_290460(o->f87C, 0xC37C), x4C);
            v = -1;
            k = 5;
            if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) != 0) {
                v = x4C;
            } else if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x20) != 0) {
                v = 1;
                k = 6;
            }
            if (v == -1) {
                break;
            }
            o->f5FC4 = v;
            UiFadeWidgetAlpha_290690(o->f87C, 0xC38F, 0.0f, 0.125f, -1.0f);
            UiFadeWidgetAlpha_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
            UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
            o->f5FC2 = o->f5FC2 + 1;
            insect_InsectBattlePlaySe_4f45b0(o, k);
            break;
        case 4:
            if (UiGetWidgetAlpha_290770(o->f87C, 0xC378) <= D_0047D88C) {
                o->f5FC2 = -1;
                t = o->f5FC4;
                o->f5FC3 = t;
                if (t == 0) {
                    n = insect_InsectBattleGetStep_50d6a0(o, 0);
                    insect_InsectBattleSetState_50d8c0(o, 0x28, 0, -1);
                    insect_InsectBattleSetStep_50d7a0(o, n, 0, -1);
                }
                insect_InsectBattleClearFlag_50da90(o, 0x4E);
                o->f4FBC &= 0xEF;
            }
            break;
        }
        UiUpdateWidgets_2913a0(o->f87C);
        insect_InsectCursorSetInput_511090(o->f4F90);
        b = o->f4FBC;
        c = (b & 0x10) != 0;
        if (c != 0) {
            o->f4FBC = b | 0x20;
            insect_InsectCursorSetInput_511090(o->f4F90);
            o->f4FBC &= 0xDF;
        }
    }
}
