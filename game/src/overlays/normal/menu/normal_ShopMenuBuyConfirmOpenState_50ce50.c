/* rgp:protos */
#define RGP_SELF_normal_ShopMenuBuyConfirmOpenState_50ce50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050CE50 -- twin of normal_FUN_0050FDD0 on the same gp handle
 * D_004845CC.  Here the record comes through one more indirection
 * (D_00484644->f00) and a NULL there is an early `return 0` that skips the
 * shared func_28EDE0 tail -- `bnel $16,$0` PAST the `b` is that test.
 */

typedef struct Hdl { u8 pad00[0x14]; s16 f14; } Hdl;
typedef struct Rec { u8 pad00[0x10]; s16 *f10; } Rec;
typedef struct Own { Rec *f00; } Own;

extern f32   D_0047D460;          /* gp - 0x7D10 */
extern void *D_004845C4;          /* gp - 0xBAC  */
extern void *D_004845CC;          /* gp - 0xBA4  */
extern void *D_004845D0;          /* gp - 0xBA0  */
extern Own  *D_00484644;          /* gp - 0xB2C  */
extern u8    D_00484650;          /* gp - 0xB20  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuBuyConfirmOpenState_50ce50(void *a, s32 b)
{
    Hdl *h;
    Rec *r;
    s32  v;

    if (b != 0) {
        r = D_00484644->f00;
        if (r == 0) {
            return 0;
        }
        h = ((Hdl *)UiEntryListFindByTag_28ea40(D_004845D0, 0x7533));
        v = *r->f10;
        normal_ShopMenuConfirmTextSet_5092e0(v, h->f14, ShopRowGetPrice_3ce6e0(D_00484644), 0);
        UiSetWidgetsVisibleById_291110(D_004845CC, 0x63, 1, 1);
        UiSetWidgetPos_290f60(D_004845CC, 0x63, 0x8C, 0x72);
        UiFadeWidgetAlpha_290690(D_004845CC, 0x63, 1.0f, D_0047D460, 0.0f);
        D_00484650 = 0;
        normal_ShopMenuYesNoHighlight_509270(0, D_004845CC, 0x65);
        UiSetWidgetPos_290f60(D_004845CC, 0x66, 0x2C, 0x58);
        UiEntryListSelectByTag_28ea90(D_004845D0, 0x7536, 0);
    }
    StateMachineSetState_28ede0(D_004845C4, 0x753C, 0);
    return 1;
}
