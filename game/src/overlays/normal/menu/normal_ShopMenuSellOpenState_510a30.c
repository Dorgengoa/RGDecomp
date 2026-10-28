/* rgp:protos */
#define RGP_SELF_normal_ShopMenuSellOpenState_510a30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00510A30 -- the item-menu page's one-shot build: the 0x19/0x32
 * frame, the normal_D_00527E70 layout box, the party rig, the 0x7534 caption anchored
 * off its own handle, and the four 0x4F list rows.  The 0x32-fade test at the
 * end runs on EVERY call.
 *
 * `$4` is never read -- another member of the f(void *, s32) state-handler
 * family; the guard is on `b`, and the function returns 1.
 * `addiu $6,$0,1 / daddu $7,$6,$0` and `addiu $6,$0,0x18 / daddu $7,$6,$0` are
 * mwcc SHARING a constant between two arguments, not two source constants --
 * func_28DB40 takes EIGHT arguments, four of them in $8..$11.
 * The final func_290690 never loads `$f12`: it still holds the 1.0f the
 * `c.eq.s` compare materialised, so the literal is CSEd across the test and
 * the call.  Writing 1.0f in both places is what produces that.
 * `mtc1 $2,$f12 / nop / c.eq.s` is the mfc1-hazard nop, compiler output. */

typedef struct Hdl  { u8 pad00[4]; s16 f04; s16 f06; u8 pad08[0x14 - 8];
                      s16 f14; s16 f16; } Hdl;
typedef struct Ctx  { u8 pad00[0x18]; s32 f18; } Ctx;
typedef struct Sess { u8 pad00[0x10]; s8 f10; s8 f11; } Sess;

extern u8 normal_D_00527E70;

extern f32   D_0047D488;          /* gp - 0x7CE8 */
extern f32   D_0047D4B4;          /* gp - 0x7CBC */
extern f32   D_0047D4B8;          /* gp - 0x7CB8 */
extern void *D_004845C4;          /* gp - 0xBAC  */
extern void *D_004845C8;          /* gp - 0xBA8  */
extern void *D_004845CC;          /* gp - 0xBA4  */
extern void *D_004845D0;          /* gp - 0xBA0  */
extern Sess *D_004845D4;          /* gp - 0xB9C  */
extern void *D_0048467C;          /* gp - 0xAF4  */

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

s32 normal_ShopMenuSellOpenState_510a30(void *a, s32 b)
{
    s32  i;
    Hdl *h;

    if (b != 0) {
        UiSetWidgetsVisibleById_291110(D_004845C8, 0x19, 1, 1);
        UiSetSpriteU_28f930(D_004845C8, 0x19, 0xD0, 0);
        UiSetWidgetAlpha_2907a0(D_004845C8, 0x3C, 0.0f);
        UiSetWidgetVisible_290010(D_004845C8, 0x32, 1, -1);
        UiSetWidgetPos_290f60(D_004845C8, 0x32, 0x200, 0x49);
        UiMoveWidgetUniform_290f50(D_004845C8, 0x32, 0x50, 0x49, D_0047D4B8, 0);
        UiFadeWidgetAlpha_290690(D_004845C8, 0x32, 1.0f, 0.0625f, 0.0f);
        UiSelFrameInit_28da30(&normal_D_00527E70, D_004845C8, 0x3F);
        UiSelFrameSetRect_28db40(&normal_D_00527E70, 0x3F, 0x18, 0x18, 0x2A, 0x30, 0x50, 0x49);
        UiSelFrameCalcTileCounts_28d9d0(&normal_D_00527E70);
        D_004845D4->f10 = 6;
        D_004845D4->f11 = 0;
        normal_ShopMenuSellTabsLayout_50e980(0x38, 0);
        MenuItemGridMarkInUse_2a4860(D_004845D4, 0x3C);
        MenuFillItemGrid_2a4b40(D_004845D4, 0x3D);
        MenuFillItemCounts_2a3d90(D_004845D4, 0x3E);
        h = ((Hdl *)UiEntryListFindByTag_28ea40(D_004845D0, 0x7534));
        h->f16 = 0;
        h->f14 = 0;
        UiSetWidgetPos_290f60(D_004845C8, 0x40, h->f04, h->f06);
        normal_ShopMenuItemInfoShow_509520(InvFindByCategoryIndex_3c86e0(((Ctx *)GetGameData_1fede0())->f18, 0, 0, 0, 0, 0),
                            0x34, 0x33, 0x57, 0x15E, D_0047D488);
        UiSetWidgetsVisibleById_291110(D_004845CC, 0x57, 1, 1);
        UiSetWidgetAlpha_2907a0(D_004845CC, 0x57, 0.0f);
        UiSetSpriteX_28fcd0(D_004845CC, 0x57, -1, 9);
        UiSetWidgetVisible_290010(D_004845CC, 0x5B, 1, -1);
        UiSetWidgetAlpha_2907a0(D_004845CC, 0x5B, 0.0f);
        for (i = 0; i < 4; i++) {
            UiSetSubItemFlags_28ef30(D_004845CC, 0x4F, (long long)(0x20), 1, i);
            UiSetSpriteFlags_290bd0(D_004845CC, 0x4F, (long long)(8), 1, i, 0);
        }
        D_0048467C = 0;
    }
    if (UiGetWidgetAlpha_290770(D_004845C8, 0x32) == 1.0f) {
        UiFadeWidgetAlpha_290690(D_004845C8, 0x3C, 1.0f, D_0047D4B4, -1.0f);
        StateMachineSetState_28ede0(D_004845C4, 0x7543, 0);
    }
    return 1;
}
