/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuSelectKing_4fed30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004FED30 -- 776 bytes, 194 instructions, 29 calls, 7 conditional
 * branches, br/ins 0.036.  insect_InsectBattleGetStep_50d6a0(o, 2) state dispatch family;
 * header is insect_InsectBattleMenuTeamSelect_5004f0.c.  Compare chain 0x1D, 0x15, 0x12, 1 ->
 * source order 1, 0x12, 0x15, 0x1D (blocks 4FED90, 4FEEBC, 4FEF0C, 4FEF7C),
 * with 1 falling through into 0x12 and 0x12 into 0x15.
 *
 * Both centring expressions are signed DIVISIONS, not shifts: retail emits the
 * bgez / addiu 1 / sra pair for each, which `>> 1` does not produce.
 */

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    void *f87C;                 /* +0x087C */
    u8    pad880[0x4F90 - 0x880];
    u8    f4F90[0x2C];          /* +0x4F90 */
    u8    f4FBC;                /* +0x4FBC */
    u8    pad4FBD[0x5054 - 0x4FBD];
    u8    f5054[0x18];          /* +0x5054 */
    u8    f506C[0x4];           /* +0x506C */
    u8    pad5070[0x5DA0 - 0x5070];
    s32   f5DA0;                /* +0x5DA0 */
    s32   f5DA4;                /* +0x5DA4 */
} Ins;

extern u8 insect_D_00523F00[];

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

void insect_InsectBattleMenuSelectKing_4fed30(Ins *o)
{
    void *g;
    void *p19;
    s32 i;

    g = o->f5054;
    p19 = o->f506C;

    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        UiSetWidgetAlpha_2907a0(o->f87C, 0xC38F, 0.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC38F, 1.0f, 0.125f, -1.0f);
        UiWindowFrameLayoutMaybe_392bb0(g, UiFindWidget_290460(o->f87C, 0xC390), 0x140, 0x60, 0);
        InsectUiWindowFillSetSizeMaybe_3938f0(g, UiFindWidget_290460(o->f87C, 0xC391), 316.0f, 92.0f);
        UiSetTextString_28f510(o->f87C, 0xC390, ((s32)insect_InsectMsgGet_512b70(p19, 9)), 0);
        UiSetTextPos_28f5d0(o->f87C, 0xC390, 0x30, 0x10, 0);
        UiSetTextString_28f510(o->f878, 0x753C, ((s32)insect_InsectMsgGet_512b70(p19, 0xA)), 0);
        UiSetTextPos_28f5d0(o->f878, 0x753C,
                    insect_InsectMsgCenterX_512b10(p19, 0xA, o->f5DA0 + 0x40), 8, 0);
        UiSetWidgetsVisibleById_291110(o->f878, 0x753D, 0, 1);
        insect_InsectBattleSetStep_50d7a0(o, 0x12, 2, -1);
        /* fallthrough */
    case 0x12:
        UiSetWidgetPos_290f60(o->f87C, 0xC390, (o->f5DA0 - 0x140) / 2,
                    (o->f5DA4 - 0x60) / 2);
        insect_InsectBattleSetStep_50d7a0(o, 0x15, 2, -1);
        /* fallthrough */
    case 0x15:
        UiSetWidgetVisible_290010(o->f87C, 0xC38F, 1, -1);
        UiSetWidgetVisible_290010(o->f87C, 0xC392, 1, -1);
        insect_InsectCursorSetPushPage_511cf0(o->f4F90, 0, 1);
        o->f4FBC = o->f4FBC & 0xFD;
        insect_InsectBattleSetStep_50d7a0(o, 5, 0, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
        break;
    case 0x1D:
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523F00, 1);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC38F, 0.0f, 0.125f, -1.0f);
        i = 0;
        do {
            UiSetTextColor_290a40(o->f878, 0x7545, 0xFF7F7F7F, i);
            i++;
        } while (i < 5);
        insect_InsectBattleSetState_50d8c0(o, 0xE, 0, -1);
        insect_InsectCursorSetPushPage_511cf0(o->f4F90, 8, 1);
        break;
    }
}
