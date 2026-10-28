/* rgp:protos */
#define RGP_SELF_normal_ShopMenuSellConfirmOpenState_50fdd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050FDD0 -- the 0x63/0x65/0x66 dialogue-open handler.  Twin of
 * normal_FUN_0050CE50: same func_291110 / func_290F60 / func_290690 /
 * normal_ShopMenuYesNoHighlight_509270 spine on the gp handle D_004845CC, differing in the
 * record it reads, the flag it writes and two message ids.
 */

typedef struct Hdl { u8 pad00[0x14]; s16 f14; } Hdl;
typedef struct Rec { u8 pad00[0x10]; s16 *f10; } Rec;

extern u8 normal_D_00527E70[];

extern f32   D_0047D460;          /* gp - 0x7D10 */
extern void *D_004845C4;          /* gp - 0xBAC  */
extern void *D_004845CC;          /* gp - 0xBA4  */
extern void *D_004845D0;          /* gp - 0xBA0  */
extern Rec  *D_0048467C;          /* gp - 0xAF4  */
extern u8    D_00484684;          /* gp - 0xAEC  */

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

s32 normal_ShopMenuSellConfirmOpenState_50fdd0(void *a, s32 b)
{
    Hdl *h;
    Rec *r;
    s32  v;

    if (b != 0) {
        h = ((Hdl *)UiEntryListFindByTag_28ea40(D_004845D0, 0x7535));
        r = D_0048467C;
        v = *r->f10;
        normal_ShopMenuConfirmTextSet_5092e0(v, h->f14, ((short)ItemGetSellPrice_3d4320(r)), 1);
        UiSetWidgetsVisibleById_291110(D_004845CC, 0x63, 1, 1);
        UiSetWidgetPos_290f60(D_004845CC, 0x63, 0x8C, 0x72);
        UiFadeWidgetAlpha_290690(D_004845CC, 0x63, 1.0f, D_0047D460, 0.0f);
        D_00484684 = 1;
        normal_ShopMenuYesNoHighlight_509270(1, D_004845CC, 0x65);
        UiSetWidgetPos_290f60(D_004845CC, 0x66, 0x7C, 0x58);
        UiEntryListSelectByTag_28ea90(D_004845D0, 0x7536, 0);
    }
    UiSelFrameAnimStep_28d820(normal_D_00527E70, 0x3F);
    StateMachineSetState_28ede0(D_004845C4, 0x7549, 0);
    return 1;
}
