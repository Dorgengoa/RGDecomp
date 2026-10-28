/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuTeamConfirm_5001e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005001E0 -- 776 bytes, 194 instructions, 27 calls, 8 conditional
 * branches, br/ins 0.041.  insect_InsectBattleGetStep_50d6a0(o, 2) state dispatch family;
 * header is insect_InsectBattleMenuTeamSelect_5004f0.c.  Compare chain 0xB, 0xA, 0x1E, 0x1F, 0x1D,
 * 0x1A, 1, so source order is 1, 0x1A, 0x1D, 0x1F, 0x1E, 0xA, 0xB -- note
 * 0x1F comes BEFORE 0x1E.  Source case order need not be ascending; the block
 * addresses (500320, 500384, 5003BC for 0x1D, 0x1F, 0x1E) are the authority.
 * Case 1 falls through into 0x1A, and 0xA / 0xB are the usual empty pair
 * (0xB keeps its beql to .L005004D8, 0xA gets a plain beq to .L005004D4).
 *
 * insect_InsectBattleConfirmDialogOpen_50eaf0's last argument 1 has no instruction of its own: it is
 * the constant case 1's own COMPARE built.
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

extern u8 insect_D_00523E40[];

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

void insect_InsectBattleMenuTeamConfirm_5001e0(Ins *o)
{
    s32 x4C;
    s32 x48;
    s32 x44;
    s32 x40;
    s32 x3C;
    s32 x38;
    void *g;
    void *p19;
    void *w;
    u8  b;

    g = o->f5054;

    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        insect_InsectBattleConfirmDialogOpen_50eaf0(o->f5DA0, o->f5DA4, o->f506C, 1);
        insect_InsectCursorSetGetCurCell_511a90(o->f4F90, &x4C, &x48);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523E40, 1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1A, 2, -1);
        /* fallthrough */
    case 0x1A:
        o->f4FBC = o->f4FBC & 0xFD;
        insect_InsectCursorSetGetCell_511a40(o->f4F90, 7, &x44, &x40);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523E40, 0);
        w = UiFindWidget_290460(o->f87C, 0xC37B);
        b = !(x44 != 0);
        InsectUiConfirmButtonSetSelectedMaybe_392b20(g, w, b);
        InsectUiConfirmButtonSetSelectedMaybe_392b20(g, UiFindWidget_290460(o->f87C, 0xC37C), x44);
        break;
    case 0x1D:
        o->f4FBC = o->f4FBC | 2;
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 0x1F, 2, -1);
        break;
    case 0x1F:
        if (UiGetWidgetAlpha_290770(o->f87C, 0xC378) <= 0.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
        }
        break;
    case 0x1E:
        UiGetWidgetPos_2910a0(o->f878, 0x753E, &x3C, &x38);
        UiMoveWidgetUniform_290f50(o->f878, 0x753E, o->f5DA0 - 0xE4, x38, 0.5f, 0);
        UiFadeWidgetAlpha_290690(o->f878, 0x7547, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f878, 0x7555, 0.0f, 0.125f, -1.0f);
        p19 = o->f506C;
        UiSetTextString_28f510(o->f878, 0x753C, ((s32)insect_InsectMsgGet_512b70(p19, 7)), 0);
        UiSetTextPos_28f5d0(o->f878, 0x753C,
                    insect_InsectMsgCenterX_512b10(p19, 7, o->f5DA0 + 0x40), 8, 0);
        UiSetWidgetSubItemValue_291250(o->f878, 0x753D, 0, (long long)(0));
        break;
    case 0xA:
        break;
    case 0xB:
        break;
    }
}
