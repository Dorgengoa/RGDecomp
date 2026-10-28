/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuSpecialConfirm_4fbcc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004FBCC0 -- 948 bytes, 237 instructions, 33 calls, 11 conditional
 * branches, br/ins 0.046.  insect_InsectBattleGetStep_50d6a0(o, 2) state dispatch family;
 * header is insect_InsectBattleMenuTeamSelect_5004f0.c.  A compare CHAIN of seven testing
 * 0x24, 0x23, 0x22, 0x1C, 0x1B, 3, 1, so source order is the REVERSE:
 * 1, 3, 0x1B, 0x1C, 0x22, 0x23, 0x24 -- and the block addresses run
 * FBD44, FBDCC, FBE30, FBE40, FBEAC, FBF98, FC00C in exactly that order.
 * 0x1B falls through into 0x1C.
 *
 * Case 0x1B's argument 0x1C has no instruction of its own: it is the constant
 * case 0x1C's COMPARE built, CSE'd into the arm.
 *
 * o->f4F90 is an array member (retail rematerialises the addiu at all three
 * sites); g and p19 really are hoisted locals and retail emits p19's addiu
 * first, so it is written first.
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
    u8    pad5070[0x5B24 - 0x5070];
    s32   f5B24;                /* +0x5B24 */
    u8    pad5B28[0x4];
    s32   f5B2C;                /* +0x5B2C */
    u8    pad5B30[0x5DA0 - 0x5B30];
    s32   f5DA0;                /* +0x5DA0 */
    s32   f5DA4;                /* +0x5DA4 */
} Ins;

typedef struct Rec { u8 pad00[0x66]; s8 f66; } Rec;

extern u8 insect_D_00524080[];

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

void insect_InsectBattleMenuSpecialConfirm_4fbcc0(Ins *o)
{
    s32 x4C;
    s32 x48;
    void *p19;
    void *g;
    void *w;
    Rec *r;
    u8 b;

    p19 = o->f506C;
    g = o->f5054;

    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        UiFadeWidgetAlpha_290690(o->f87C, 0xC378, 1.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        insect_InsectBattleConfirmDialogOpen_50eaf0(o->f5DA0, o->f5DA4, p19, 0x13);
        insect_InsectBattleSetStep_50d7a0(o, 3, 2, -1);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00524080, 1);
        break;
    case 3:
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00524080, 0);
        if (UiGetWidgetAlpha_290770(o->f87C, 0xC378) >= 1.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x1B, 2, -1);
        }
        break;
    case 0x1B:
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 2, -1);
        /* fallthrough */
    case 0x1C:
        insect_InsectCursorSetGetCurCell_511a90(o->f4F90, &x4C, &x48);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00524080, 0);
        w = UiFindWidget_290460(o->f87C, 0xC37B);
        b = !(x4C != 0);
        InsectUiConfirmButtonSetSelectedMaybe_392b20(g, w, b);
        InsectUiConfirmButtonSetSelectedMaybe_392b20(g, UiFindWidget_290460(o->f87C, 0xC37C), x4C);
        break;
    case 0x22:
        o->f5B2C = 0;
        o->f5B24 = 0;
        r = ((Rec *)insect_InsectBattleGetSpecialRec_50db30(o));
        if (r != 0) {
            UiFadeWidgetAlpha_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
            UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
            if (r->f66 == 0) {
                UiFadeWidgetAlpha_290690(o->f878, 0x7580, 1.0f, 0.125f, -1.0f);
                UiFadeWidgetAlpha_290690(o->f878, 0x755F, 1.0f, 0.125f, -1.0f);
            } else {
                UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
            }
        }
        insect_InsectBattleSetStep_50d7a0(o, 0x23, 2, -1);
        break;
    case 0x23:
        if (UiGetWidgetAlpha_290770(o->f87C, 0xC378) <= 0.0f) {
            insect_InsectBattlePopState_50d880(o, 0);
            insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
            insect_InsectBattlePopState_50d880(o, 2);
            insect_InsectBattleSetStep_50d7a0(o, 0x1B, 2, -1);
            insect_InsectCursorSetPopPage_511ca0(o->f4F90);
            o->f4FBC = o->f4FBC | 2;
        }
        break;
    case 0x24:
        UiFadeWidgetAlpha_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 0x25, 2, -1);
        break;
    }
}
