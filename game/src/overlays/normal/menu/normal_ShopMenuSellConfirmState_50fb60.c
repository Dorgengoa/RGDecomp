/* rgp:protos */
#define RGP_SELF_normal_ShopMenuSellConfirmState_50fb60 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050FB60 -- the map-screen tick: pumps the 0x4B2570 pad object,
 * reads the panel's mode out of func_28EC60 and drives one of four branches,
 * then re-lays the 0x66 widget from the smoothed scroll value in D_00484678.
 *
 * `ori $5, $0, 0x8000` rather than `addiu` is the pad mask being an UNSIGNED
 * 16-bit constant -- 0x8000 does not fit a signed 16-bit immediate, and that is
 * the source constant, not a cast.
 * The two `sb` stores to D_00484684 sit in their call's delay slot because they
 * are written BEFORE the call in the source, and the stored value is also that
 * call's first argument, which is why `$4` carries both.
 * `D_00484684 * 80 + 0x2C` is the row pitch: mwcc strength-reduces *80 to
 * sll/addu/sll.
 *
 * A NAMED LOCAL FOR THE PRODUCT (`v`) IS THE WHOLE FLOAT STORY, AND IT DOES
 * THREE THINGS AT ONCE.  Written inline as one expression mwcc contracts the
 * product into `adda.s`/`madd.s` (3 words long), picks the IEEE float->int
 * path instead of the R5900 `cvt.w.s`, and puts the sum's operands in the
 * wrong `fs`/`ft` slots -- and the last of those is right length, so only a
 * byte compare sees it.  `#pragma usefloatacc off` and `#pragma fast_fptosi on`
 * each also fix their own symptom, and with `v` named BOTH ARE INERT (measured
 * here by removing them singly and together, still MATCH), so they are not in
 * this file.  levers.d/title-float-const-operand.md's rule says name the
 * LITERAL; the operand that had to be named here is the CALL PRODUCT.
 *
 * `m` is func_28E170's return, NOT func_28EC60's -- the `daddu $16,$2,$0` sits
 * in the NEXT call's delay slot, which reads as the wrong call's result. */

typedef struct Hdl  { u8 pad00[0x14]; s16 f14; } Hdl;
typedef struct Sess { u8 pad00[0x11]; s8  f11; } Sess;

extern u8 D_004B2570;
extern u8 normal_D_00527E70;

extern f32   D_0047D3B8;          /* gp - 0x7DB8 */
extern f32   D_0047D3C8;          /* gp - 0x7DA8 */
extern void *D_004845C4;          /* gp - 0xBAC  */
extern void *D_004845CC;          /* gp - 0xBA4  */
extern void *D_004845D0;          /* gp - 0xBA0  */
extern Sess *D_004845D4;          /* gp - 0xB9C  */
extern f32   D_00484678;          /* gp - 0xAF8  */
extern void *D_0048467C;          /* gp - 0xAF4  */
extern s8    D_00484684;          /* gp - 0xAEC  */

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

s32 normal_ShopMenuSellConfirmState_50fb60(void)
{
    s32 m;
    f32 v;

    m = MenuGridCursorInput_28e170(D_004845D0, &D_004B2570, 0, 0);
    UiEntryListGetCurrentData_28ec60(D_004845D0);
    if (m == 1) {
        if (D_00484684 == 0) {
            UiFadeWidgetAlpha_290690(D_004845CC, 0x67, 0.0f, D_0047D3C8, -1.0f);
            UiFadeWidgetAlpha_290690(D_004845CC, 0x57, 0.0f, D_0047D3C8, -1.0f);
            UiFadeWidgetAlpha_290690(D_004845CC, 0x63, 0.0f, D_0047D3C8, -1.0f);
            ItemSell_3d4010(D_0048467C, ((Hdl *)UiEntryListFindByTag_28ea40(D_004845D0, 0x7535))->f14);
            normal_ShopMenuMoneyRefresh_50ac80(0x15, 0x14);
            UiEntryListFindByTag_28ea40(D_004845D0, 0x7534);
            PlayMenuSe_289ef0(0x20);
            normal_ShopMenuSellTabsLayout_50e980(0x38, D_004845D4->f11);
            MenuItemGridMarkInUse_2a4860(D_004845D4, 0x3C);
            MenuFillItemGrid_2a4b40(D_004845D4, 0x3D);
            MenuFillItemCounts_2a3d90(D_004845D4, 0x3E);
            StateMachineSetState_28ede0(D_004845C4, 0x754B, 0);
        } else {
            StateMachineSetState_28ede0(D_004845C4, 0x754A, 0);
        }
    } else if (m == 2) {
        PlayMenuSe_289ef0(6);
        StateMachineSetState_28ede0(D_004845C4, 0x754A, 0);
    } else if (PadIsTriggered_1839f0(&D_004B2570, 0x8000) != 0) {
        if (D_00484684 == 1) {
            PlayMenuSe_289ef0(4);
        }
        D_00484684 = 0;
        normal_ShopMenuYesNoHighlight_509270(0, D_004845CC, 0x65);
    } else if (PadIsTriggered_1839f0(&D_004B2570, 0x2000) != 0) {
        if (D_00484684 == 0) {
            PlayMenuSe_289ef0(4);
        }
        D_00484684 = 1;
        normal_ShopMenuYesNoHighlight_509270(1, D_004845CC, 0x65);
    }
    PhaseAdvanceWrapPi_28b630(&D_00484678, D_0047D3B8);
    v = 8.0f * Sinf_128fd0(D_00484678);
    UiMoveWidgetUniform_290f50(D_004845CC, 0x66, (s32)(v + (D_00484684 * 80 + 0x2C)), 0x58, 0.25f, 0
);
    UiSelFrameAnimStep_28d820(&normal_D_00527E70, 0x3F);
    return 1;
}
