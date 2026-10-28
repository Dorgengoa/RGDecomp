/* rgp:protos */
#define RGP_SELF_normal_ShopMenuBuyQtyPanelLayout_50bb40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050BB40 -- builds the 0x4A/0x4D/0x77-0x7A/0x4F item panel for one
 * entry and returns the mode func_3CE860 reported.
 * # m2c emits `func_291110()` with no arguments in the else arm; the two arms
 * differ only in ONE argument and $7 is materialised before the branch.
 * The `dsll32 $2,$rX,0 / dsra32 $2,$2,0` pairs are s32 -> s64 widening into
 * the two `sd` fields, so 3CE860 and 3CE6E0 return s32 and the fields are s64. */

extern void *D_004845CC;          /* gp - 0xBA4 */
extern void *D_004845F8;          /* gp - 0xB78 */

typedef struct Item {
    u8   pad000[0x48];
    s64  f048;
    u8   pad050[0x68 - 0x50];
    s64  f068;
    u8   pad070[0x76 - 0x70];
    s16  f076;
    s16  f078;
} Item;

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

s32 normal_ShopMenuBuyQtyPanelLayout_50bb40(s32 arg)
{
    s32 mode;
    s32 w;
    s32 v;
    Item *it;

    if (arg == 0) {
        return 0;
    }
    mode = ((short)ShopRowGetStock_3ce860((void *)arg));
    w = ((s32)UiGetWidgetSprite_28fe10(D_004845CC, 0x4C, 0));
    if (w == 0) {
        return 0;
    }
    UiSetItemIconUv_288e50(w, ShopRowGetItemIconIdMaybe_3ce890(arg), 0x28, 0x2D);
    UiSetTextString_28f510(D_004845CC, 0x4A, MsgTableLookup_28aa30(D_004845F8, 3), 0);
    if (mode == 1) {
        UiSetWidgetsVisibleById_291110(D_004845CC, 0x4D, 0, 1);
    } else {
        UiSetWidgetsVisibleById_291110(D_004845CC, 0x4D, 1, 1);
    }
    UiSetTextX_28f590(D_004845CC, 0x4A, 0xA0 - UiGetWidgetTextWidth_28f400(D_004845CC, 0x4A, 0) / 2, 0);
    UiSetTextString_28f510(D_004845CC, 0x4A, ShopRowGetItemName_3ce930(arg), 1);
    UiSetTextCenteredX_28f300(D_004845CC, 0x4A, 0xA8, 1);
    w = ((s32)UiGetWidgetSprite_28fe10(D_004845CC, 0x7A, 0));
    if (w == 0) {
        return 0;
    }
    UiSetWidgetsVisibleById_291110(D_004845CC, 0x77, 1, 1);
    UiSetWidgetsVisibleById_291110(D_004845CC, 0x78, 1, 1);
    UiSetWidgetsVisibleById_291110(D_004845CC, 0x79, 1, 1);
    UiSetWidgetsVisibleById_291110(D_004845CC, 0x7A, 1, 1);
    UiLayoutStringGlyphs_28a800(w, MsgTableLookup_28aa30(D_004845F8, 0x14), 0, 0, -2);
    UiSetWidgetPos_290f60(D_004845CC, 0x77, 0x70, 0x5A);
    UiSetWidgetPos_290f60(D_004845CC, 0x78, 0x3E, 0x72);
    UiSetWidgetPos_290f60(D_004845CC, 0x79, 0xB4, 0x44);
    UiSetWidgetPos_290f60(D_004845CC, 0x7A, 0x3E, 0x44);
    it = ((Item *)UiGetWidgetSubItem_28f2b0(D_004845CC, 0x4F, 0));
    if (it == 0) {
        return 0;
    }
    v = ShopRowGetPrice_3ce6e0(arg);
    if (mode == 0x64) {
        it->f078 = 0;
        it->f076 = 0;
        UiSetSpriteSizeUvSize_28f670(D_004845CC, 0x4F, 0x1A, 0x10, 0x1A, 0x10, 0);
    } else {
        it->f076 = 0xC;
        it->f078 = 0x10;
        it->f068 = mode;
        UiSetSpriteSizeUvSize_28f670(D_004845CC, 0x4F, 0, 0, 0, 0, 0);
    }
    it->f048 = v;
    normal_ShopMenuBuyTotalPriceSet_50bb00(v, 1);
    return mode;
}
