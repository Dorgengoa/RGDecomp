/* rgp:protos */
#define RGP_SELF_normal_InsectEntryNoFundsMsgOpenState_523450 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00523450 -- the 0x1E-widget phase handler on the STATIC widget
 * normal_D_005281A0 (not a gp handle), same 0x34-Layout family as
 * normal_FUN_0050F960: frame -0x50, Layout at sp+0x10, memset 0x34.
 *
 * f(void *, s32), `$4` never read, guard on `b`, returns 1.  Only the guard
 * branches; everything in the block is straight-line.  This member writes
 * Layout f08 (0xAA) and leaves f20..f30 at the memset's zero, so the second
 * word of the pad is a real member here.  `sw $5,0x28($29)` is the scheduler
 * reusing the register that already holds the widget id 0x1E for `f18 = 0x1E`.
 *
 * The tail is UNGUARDED: `c.lt.s $f0,$f1` against an inline 1.0f with a
 * `bc1tl` PAST the call, so the source test is `>= 1.0f` and the call is the
 * fall-through side.  `addiu $4,$28,-0x7C8` is the ADDRESS of the small-data
 * object D_004849A8, not a pointer load.
 */

typedef struct Layout {
    void *f00;
    s32   f04;
    s32   f08;
    s32   f0C;
    s32   f10;
    s32   f14;
    s32   f18;
    s32   f1C;
    s32   f20;
    s32   f24;
    s32   f28;
    s32   f2C;
    s16   f30;
} Layout;

extern u8    normal_D_005281A0[];
extern u8    normal_D_005281C0[];

extern f32   D_0047D7C4;          /* gp - 0x79AC */
extern s32   D_004849A8;          /* gp - 0x7C8  */
extern void *D_004849B4;          /* gp - 0x7BC  */

extern void  memset(void *p, s32 v, s32 n);
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

s32 normal_InsectEntryNoFundsMsgOpenState_523450(void *a, s32 b)
{
    Layout lay __attribute__((aligned(16)));

    if (b != 0) {
        UiSetTextString_28f510(normal_D_005281A0, 0x1E, MsgTableLookup_28aa30(D_004849B4, 7), 0);

        memset(&lay, 0, 0x34);
        lay.f00 = UiGetWidgetSprite_28fe10(normal_D_005281A0, 0x1E, 0);
        lay.f04 = ((s32)UiGetWidgetText_28f620(normal_D_005281A0, 0x1E, 0));
        lay.f08 = 0xAA;
        lay.f10 = 0x3B;
        lay.f14 = 0x13;
        lay.f18 = 0x1E;
        lay.f1C = 0xB;
        UiGetWidgetTextHeight_28f3d0(normal_D_005281A0, 0x1E, 0);
        DrawEnvGetHeight_1451d0(GetDrawCtx_15de80());
        UiWindowFitToText_28d0c0(&lay, 0, 0, 0);

        UiSetWidgetsVisibleById_291110(normal_D_005281A0, 0x1E, 1, 1);
        UiSetWidgetAlpha_2907a0(normal_D_005281A0, 0x1E, 0.0f);
        UiFadeWidgetAlpha_290690(normal_D_005281A0, 0x1E, 1.0f, D_0047D7C4, -1.0f);
        UiEntryListSelectByTag_28ea90(normal_D_005281C0, 0x7532, 1);
    }
    if (UiGetWidgetAlpha_290770(normal_D_005281A0, 0x1E) >= 1.0f) {
        StateMachineSetState_28ede0(&D_004849A8, 0x7535, 1);
    }
    return 1;
}
