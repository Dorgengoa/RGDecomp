/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuWeaponListOpenState_4feca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004FECA0 -- sibling of normal_FUN_004FFBD0: the same 0x21 panel
 * open, gated on the u8 phase at +0x455 and latched at gp-0xC80.  This arm
 * also drives widget 0x55 and calls normal_FUN_004FFEE0 instead of
 * normal_FUN_005002F0.  Same delay-slot store placement. */

extern u8 normal_D_005278E0;

extern void *D_0048449C;          /* gp - 0xCD4  */
extern void *D_004844A0;          /* gp - 0xCD0  */
extern void *D_00484498;          /* gp - 0xCD8  */
extern u8    D_004844F0;          /* gp - 0xC80  */
extern f32   D_0047D518;          /* gp - 0x7C58 */
extern s32   D_00480518;          /* gp - 0x4C58 */
extern s32   D_00480514;          /* gp - 0x4C5C */
extern s32   D_00480510;          /* gp - 0x4C60 */
extern s32   D_004844B4;          /* gp - 0xCBC  */
extern s32   D_004844C4;          /* gp - 0xCAC  */
extern s32   D_004844BC;          /* gp - 0xCB4  */

typedef struct Ctx {
    u8   pad000[0x455];
    u8   f455;
} Ctx;
extern Ctx *D_00484454;           /* gp - 0xD1C  */

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

s32 normal_BtlChgMenuWeaponListOpenState_4feca0(void *a, s32 b)
{
    if (b != 0) {
        UiSetWidgetAlpha_2907a0(D_0048449C, 0x21, 0.0f);
        D_004844F0 = 0;
    }
    if ((D_00484454->f455 == 1) && (D_004844F0 == 0)) {
        D_004844F0 = 1;
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x21, 1, 1);
        UiEntryListSelectByTag_28ea90(D_004844A0, 0x55F4, 1);
        D_00480518 = 0;
        D_00480514 = 0;
        D_00480510 = 0;
        UiEntryListFindByTag_28ea40(D_004844A0, 0x55F4);
        D_004844B4 = 0;
        normal_BtlChgMenuWeaponListRefresh_4ffee0();
        UiSetWidgetPos_290f60(D_0048449C, 0x21, 0x2B, 0xD1);
        UiSetWidgetPos_290f60(D_0048449C, 0x26, 0x1A, 0x1D);
        UiSetWidgetPos_290f60(D_0048449C, 0x55, 0x1A, 0x1D);
        UiSetWidgetPos_290f60(D_0048449C, 0x27, 0x3C, 0x37);
        UiSelFrameInit_28da30(&normal_D_005278E0, D_0048449C, 0x28);
        UiSelFrameSetRect_28db40(&normal_D_005278E0, 0x28, 0x19, 0x17, 0x2A, 0x30, 0x2B, 0xD1);
        UiSelFrameCalcTileCounts_28d9d0(&normal_D_005278E0);
        UiSelFrameSetScrollPeriod_28d9c0(&normal_D_005278E0, 1);
        UiSetWidgetPos_290f60(D_0048449C, 0x29, 0x46, 0x46);
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x26, 1, 1);
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x55, 1, 1);
        UiSetWidgetPos_290f60(D_0048449C, 0x25, 0x183, 0x1E);
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x2A, 0, 1);
        D_004844C4 = 0;
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x43, 0, 1);
        D_004844BC = 0;
        UiSetWidgetPos_290f60(D_0048449C, 0x23, 0, 0);
        UiSetWidgetAlpha_2907a0(D_0048449C, 0x21, 0.0f);
        UiSetWidgetAlpha_2907a0(D_0048449C, 0x26, 0.0f);
        UiSetWidgetAlpha_2907a0(D_0048449C, 0x55, 0.0f);
        UiSetWidgetAlpha_2907a0(D_0048449C, 0x27, 0.0f);
        UiSetWidgetAlpha_2907a0(D_0048449C, 0x25, 0.0f);
        UiSetWidgetAlpha_2907a0(D_0048449C, 0x23, 0.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x21, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x26, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x55, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x27, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x25, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x23, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x29, 1.0f, D_0047D518, -1.0f);
    }
    if (!(UiGetWidgetAlpha_290770(D_0048449C, 0x21) < 1.0f)) {
        StateMachineSetState_28ede0(D_00484498, 0x5601, 0);
    }
    return 1;
}
