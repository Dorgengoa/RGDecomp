/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuOpenState_520e80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00520E80 -- opens the shop/menu widget set: sizes and shows a stack
 * of widget ids off the gp session pointer, then hands a four-word block to
 * func_2A33E0.  $4 is unused; the guard is on the SECOND parameter.
 * 0x3F800000 is 1.0f and 0x3D800000 0.0625f. */

typedef struct Sess {
    u8  pad000[0x10];
    s8  f010;
    s8  f011;
} Sess;

extern void *D_00484920;          /* gp - 0x850, the widget-system handle */
extern Sess *D_00484934;          /* gp - 0x83C */
extern s32   D_00484928;          /* gp - 0x848, address taken */
extern s32   D_00484948;          /* gp - 0x828 */
extern s8    D_00484954;          /* gp - 0x81C */
extern s32   D_0048494C;          /* gp - 0x824 */
extern s32   D_00484950;          /* gp - 0x820 */
extern f32   D_0047DD34;          /* gp - 0x743C */
extern u8 normal_D_00528060[];

typedef struct Widget { u8 pad000[0x20]; void *f020; } Widget;

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
typedef struct Rec { u8 pad000[0x18]; s32 f018; } Rec;
/*rgp*/
/*rgp*/
extern void memset(void *a, s32 b, s32 c);
/*rgp*/
/*rgp*/
/*rgp*/

/*rgp*/

s32 normal_ThinkMenuOpenState_520e80(void *unused, s32 show)
{
    s32 v[4] __attribute__((aligned(16)));
    s32 t;

    if (show != 0) {
        UiLayoutPanelFrame_28d580(((Widget *)UiFindWidget_290460(D_00484920, 0x7532))->f020, 0, 0, 0x186, 0x12D, 0);
        UiSetWidgetVisible_290010(D_00484920, 0x7532, 1, -1);
        UiSetWidgetPos_290f60(D_00484920, 0x7532, 0x46, 0x4B);
        UiFadeWidgetAlpha_290690(D_00484920, 0x7532, 1.0f, 0.0625f, 0.0f);
        UiSetWidgetsVisibleById_291110(D_00484920, 0x7531, 1, 1);
        UiSetWidgetPos_290f60(D_00484920, 0x7531, 0, 8);
        UiFadeWidgetAlpha_290690(D_00484920, 0x7531, 1.0f, 0.0625f, 0.0f);
        UiSetWidgetPos_290f60(D_00484920, 0x7548, 0, 8);
        UiSetWidgetsVisibleById_291110(D_00484920, 0x753D, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00484920, 0x753D, 0.0f);
        UiSetWidgetPos_290f60(D_00484920, 0x753D, 0x4D, 0x160);
        UiSetWidgetPos_290f60(D_00484920, 0x753A, 0x3E, 0x35);
        UiSelFrameInit_28da30(normal_D_00528060, D_00484920, 0x753B);
        UiSelFrameSetRect_28db40(normal_D_00528060, 0x753B, 0x18, 0x18, 0x2A, 0x30, 0x46, 0x4B);
        UiSelFrameCalcTileCounts_28d9d0(normal_D_00528060);
        UiSelFrameSetScrollPeriod_28d9c0(normal_D_00528060, 1);
        D_00484934->f010 = 6;
        D_00484934->f011 = 0;
        normal_ThinkMenuTabsLayout_520500(0x7535, 0);
        MenuFillItemGrid_2a4b40(D_00484934, 0x7539);
        MenuFillItemCounts_2a3d90(D_00484934, 0x753A);
        t = ((s32)InvFindByCategoryIndex_3c86e0(((Rec *)GetGameData_1fede0())->f018, 0, 0, 0, 0, 0));
        memset(v, 0, 0x10);
        v[0] = ((s32)UiGetWidgetSprite_28fe10(D_00484920, 0x7546, 0));
        v[1] = ((s32)UiGetWidgetSprite_28fe10(D_00484920, 0x7545, 0));
        v[2] = ((s32)UiGetWidgetText_28f620(D_00484920, 0x7545, 0));
        v[3] = ((s32)UiGetWidgetSprite_28fe10(D_00484920, 0x7547, 0));
        MenuItemInfoPopupShow_2a33e0(D_00484934, t, 0x7540, 0x753D, v, 0x4D, 0x160, -1, D_0047DD34);
        D_00484948 = 1;
        D_00484954 = 1;
        D_0048494C = -1;
        D_00484950 = -1;
    }
    StateMachineSetState_28ede0(&D_00484928, 0x7532, 1);
    return 1;
}
