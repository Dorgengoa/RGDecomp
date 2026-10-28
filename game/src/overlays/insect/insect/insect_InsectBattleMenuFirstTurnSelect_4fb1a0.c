/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuFirstTurnSelect_4fb1a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004FB1A0 -- 880 bytes, 220 instructions, 35 calls, 7 conditional
 * branches, br/ins 0.032.  Five-arm state dispatch, chain 5,4,3,2,1 and blocks
 * laid out 1,2,3,4,5, i.e. the reversed-case-order rule with source order
 * ascending.  No fall-throughs; the default is the `b` whose delay slot already
 * carries the epilogue's `ld $31`.
 *
 * The case-1 compare takes `$6` rather than `$3` because the constant 1 is
 * reused as func_290010's third ARGUMENT inside that arm -- the dispatch's own
 * constant CSE'd into the case body, the same shape as insect_FUN_005004F0's
 * case 0xA.
 */

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    void *f87C;                 /* +0x087C */
    u8    pad880[0x4F90 - 0x880];
    u8    f4F90[0x2C];          /* +0x4F90 */
    u8    f4FBC;                /* +0x4FBC */
    u8    pad4FBD[0x506C - 0x4FBD];
    u8    f506C[0x5DA0 - 0x506C];
    s32   f5DA0;                /* +0x5DA0 */
} Ins;

extern u8 insect_D_005240E0[];

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

void insect_InsectBattleMenuFirstTurnSelect_4fb1a0(Ins *o)
{
    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        UiSetWidgetVisible_290010(o->f878, 0x765C, 1, -1);
        UiSetWidgetAlpha_2907a0(o->f878, 0x753B, 0.0f);
        UiSetWidgetAlpha_2907a0(o->f878, 0x753E, 0.0f);
        UiSetWidgetAlpha_2907a0(o->f878, 0x765C, 0.0f);
        UiFadeWidgetAlpha_290690(o->f878, 0x7530, 1.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f878, 0x765C, 1.0f, 0.125f, -1.0f);
        UiSetTextString_28f510(o->f878, 0x765D, ((s32)insect_InsectMsgGet_512b70(o->f506C, 0x7D7)), 0);
        UiSetTextPos_28f5d0(o->f878, 0x765D,
                    insect_InsectMsgCenterX_512b10(o->f506C, 0x7D7, o->f5DA0 + 0x40),
                    0xA, 0);
        UiSetTextString_28f510(o->f878, 0x765E, ((s32)insect_InsectMsgGet_512b70(o->f506C, 0xC)), 0);
        UiSetTextString_28f510(o->f878, 0x765E, ((s32)insect_InsectMsgGet_512b70(o->f506C, 0xD)), 1);
        UiSetWidgetVisible_290010(o->f87C, 0xC37E, 1, -1);
        UiSetWidgetAlpha_2907a0(o->f87C, 0xC37E, 0.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 2, 2, -1);
        insect_InsectCursorSetPushPage_511cf0(o->f4F90, 7, 1);
        insect_InsectCursorSetSetCell_511c50(o->f4F90, 0, 0);
        insect_InsectCursorSetSetSize_511bd0(o->f4F90, 1, 2);
        break;
    case 2:
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_005240E0, 1);
        if (UiGetWidgetAlpha_290770(o->f878, 0x765C) >= 1.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 3, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 3, 0, -1);
            o->f4FBC = o->f4FBC & 0xFD;
        }
        break;
    case 3:
        insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_005240E0, 0);
        break;
    case 4:
        UiFadeWidgetAlpha_290690(o->f878, 0x753E, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f878, 0x765C, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f878, 0x7530, 0.0f, 0.125f, -1.0f);
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 5, 2, -1);
        break;
    case 5:
        if (UiGetWidgetAlpha_290770(o->f878, 0x7530) <= 0.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 6, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 5, 0, -1);
        }
        break;
    }
}
