/* rgp:protos */
#define RGP_SELF_normal_ShopMenuBuyQtyCursorMoveCb_50cf50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct CF50A {
    u8  pad00[8];
    s16 f08;
    u8  pad0A[6];
    s16 f10;
} CF50A;

typedef struct CF50C {
    u8  pad00[0x18];
    void *f18;
} CF50C;

typedef struct CF50O {
    s16 f00;
    u8  pad02[0x12];
    s8  f14;
} CF50O;

typedef struct CF50M {
    u8     pad00[0x10];
    CF50O *f10;
} CF50M;

typedef struct CF50S {
    CF50M *f00;
} CF50S;

typedef struct CF50R {
    u8  pad00[0x160];
    s64 f160;
} CF50R;

extern void  *D_004845CC;         /* gp - 0xBA4  */
extern CF50S *D_00484644;         /* gp - 0xB2C  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuBuyQtyCursorMoveCb_50cf50(CF50A *a)
{
    s64 lim;
    CF50C *ctx;
    CF50O *o;
    s32 t;

    if (a->f10 <= 0) {
        a->f10 = 1;
    } else if (a->f10 > 0x63) {
        a->f10 = 0x63;
    } else if (a->f08 < a->f10) {
        a->f10 = a->f08;
    }

    ctx = ((CF50C *)GetGameData_1fede0());
    UiSetSubItemFlags_28ef30(D_004845CC, 0x4F, (long long)(0x20), 1, 0);
    UiSetSubItemFlags_28ef30(D_004845CC, 0x4F, (long long)(0x20), 1, 1);
    UiSetSpriteFlags_290bd0(D_004845CC, 0x4F, (long long)(8), 1, 2, 0);

    lim = ((CF50R *)ctx->f18)->f160;
    if (lim < a->f10 * ShopRowGetPrice_3ce6e0(D_00484644)) {
        UiSetSubItemFlags_28ef30(D_004845CC, 0x4F, (long long)(0x20), -1, 1);
        UiSetSpriteFlags_290bd0(D_004845CC, 0x4F, (long long)(8), -1, 2, 0);
    }
    if (D_00484644->f00 == NULL) {
        return 0;
    }
    o = D_00484644->f00->f10;
    t = 0;
    if (o->f14 >= 0) {
        t = o->f14;
    }
    if (InvAddItemCheckedMaybe_3c6460(ctx->f18, o->f00, a->f10, t, 0) == 0) {
        UiSetSubItemFlags_28ef30(D_004845CC, 0x4F, (long long)(0x20), -1, 0);
    }
    UiSetWidgetSubItemValue_291250(D_004845CC, 0x4F, 0, (long long)(a->f10));
    normal_ShopMenuBuyTotalPriceSet_50bb00(ShopRowGetPrice_3ce6e0(D_00484644), a->f10);
    return 1;
}
