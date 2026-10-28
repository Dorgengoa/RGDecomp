/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuItemListOpenState_4ffbd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004FFBD0 -- the 0x21 panel group's one-shot open, gated on the
 * u8 phase at +0x454 reaching 1, latched by the u8 flag at gp-0xC84.
 * Retail branches AWAY on `!= 1` (`bnel`), so the guard is the plain
 * conjunction.  Six `sw $0` stores are written BEFORE the call whose delay
 * slot they fill. */

extern u8 normal_D_005278E0;

extern void *D_0048449C;          /* gp - 0xCD4  */
extern void *D_004844A0;          /* gp - 0xCD0  */
extern void *D_00484498;          /* gp - 0xCD8  */
extern u8    D_004844EC;          /* gp - 0xC84  */
extern f32   D_0047D518;          /* gp - 0x7C58 */
extern s32   D_00480508;          /* gp - 0x4C68 */
extern s32   D_00480504;          /* gp - 0x4C6C */
extern s32   D_00480500;          /* gp - 0x4C70 */
extern s32   D_004844B0;          /* gp - 0xCC0  */
extern s32   D_004844C4;          /* gp - 0xCAC  */
extern s32   D_004844B8;          /* gp - 0xCB8  */

typedef struct Ctx {
    u8   pad000[0x454];
    u8   f454;
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
/*rgp*/

s32 normal_BtlChgMenuItemListOpenState_4ffbd0(void *a, s32 b)
{
    if (b != 0) {
        UiSetWidgetAlpha_2907a0(D_0048449C, 0x21, 0.0f);
        D_004844EC = 0;
    }
    if ((D_00484454->f454 == 1) && (D_004844EC == 0)) {
        D_004844EC = 1;
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x21, 1, 1);
        UiEntryListSelectByTag_28ea90(D_004844A0, 0x55F3, 1);
        D_00480508 = 0;
        D_00480504 = 0;
        D_00480500 = 0;
        UiEntryListFindByTag_28ea40(D_004844A0, 0x55F3);
        D_004844B0 = 0;
        normal_BtlChgMenuItemListBuild_5002f0();
        UiSetWidgetPos_290f60(D_0048449C, 0x21, 0x2B, 0xD1);
        UiSetWidgetPos_290f60(D_0048449C, 0x26, 0x1A, 0x1D);
        UiSetWidgetPos_290f60(D_0048449C, 0x27, 0x3C, 0x37);
        UiSelFrameInit_28da30(&normal_D_005278E0, D_0048449C, 0x28);
        UiSelFrameSetRect_28db40(&normal_D_005278E0, 0x28, 0x19, 0x17, 0x2A, 0x30, 0x2B, 0xD1);
        UiSelFrameCalcTileCounts_28d9d0(&normal_D_005278E0);
        UiSelFrameSetScrollPeriod_28d9c0(&normal_D_005278E0, 1);
        UiSetWidgetPos_290f60(D_0048449C, 0x29, 0x46, 0x46);
        normal_BtlChgMenuItemGridLayout_5000b0();
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x26, 1, 1);
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x55, 0, 1);
        UiSetWidgetPos_290f60(D_0048449C, 0x25, 0x183, 0x1E);
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x2A, 0, 1);
        D_004844C4 = 0;
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x43, 0, 1);
        D_004844B8 = 0;
        UiSetWidgetPos_290f60(D_0048449C, 0x23, 0, 0);
        UiSetWidgetAlpha_2907a0(D_0048449C, 0x21, 0.0f);
        UiSetWidgetAlpha_2907a0(D_0048449C, 0x26, 0.0f);
        UiSetWidgetAlpha_2907a0(D_0048449C, 0x27, 0.0f);
        UiSetWidgetAlpha_2907a0(D_0048449C, 0x25, 0.0f);
        UiSetWidgetAlpha_2907a0(D_0048449C, 0x23, 0.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x21, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x26, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x27, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x25, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x23, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x29, 1.0f, D_0047D518, -1.0f);
    }
    if (!(UiGetWidgetAlpha_290770(D_0048449C, 0x21) < 1.0f)) {
        StateMachineSetState_28ede0(D_00484498, 0x55FA, 0);
    }
    return 1;
}
