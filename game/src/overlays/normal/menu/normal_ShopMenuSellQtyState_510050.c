/* rgp:protos */
#define RGP_SELF_normal_ShopMenuSellQtyState_510050 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct N50O {
    u8  pad00[8];
    s16 f08;
    u8  pad0A[6];
    s16 f10;
} N50O;

typedef struct N50W {
    u8  pad00[0x14];
    s32 f14;
} N50W;

extern f32   D_0047D4AC;          /* gp - 0x7CC4 */
extern N50W *D_004845D0;          /* gp - 0xBA0  */
extern void *D_004845CC;          /* gp - 0xBA4  */
extern void *D_004845C4;          /* gp - 0xBAC  */
extern void *D_0048467C;          /* gp - 0xAF4  */
extern u8    D_004B2570[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuSellQtyState_510050(s32 a, s32 b)
{
    N50O *o;
    s32   m;

    if (b != 0) {
        UiEntryListSelectByTag_28ea90(D_004845D0, 0x7535, 0);
    }
    m = MenuGridCursorInput_28e170(D_004845D0, D_004B2570, 1, 0);
    o = ((N50O *)UiEntryListGetCurrentData_28ec60(D_004845D0));
    if (m == 1) {
        PlayMenuSe_289ef0(5);
        UiFadeWidgetAlpha_290690(D_004845CC, 0x48, 0.0f, D_0047D4AC, -1.0f);
        StateMachineSetState_28ede0(D_004845C4, 0x7548, 0);
    } else if (m == 2) {
        PlayMenuSe_289ef0(6);
        StateMachineSetState_28ede0(D_004845C4, 0x7547, 0);
    } else if (D_004845D0->f14 == 1) {
        o->f10 += 0xA;
        if (o->f08 < o->f10) {
            o->f10 = o->f08;
        }
        UiSetWidgetSubItemValue_291250(D_004845CC, 0x4F, 0, (long long)(o->f10));
        normal_ShopMenuSellTotalPriceSet_50ec80(ItemGetSellPrice_3d4320(D_0048467C), o->f10);
    } else if (D_004845D0->f14 == 2) {
        o->f10 -= 0xA;
        if (o->f10 <= 0) {
            o->f10 = 1;
        }
        UiSetWidgetSubItemValue_291250(D_004845CC, 0x4F, 0, (long long)(o->f10));
        normal_ShopMenuSellTotalPriceSet_50ec80(ItemGetSellPrice_3d4320(D_0048467C), o->f10);
    }
    return 1;
}
