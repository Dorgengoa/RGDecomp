/* rgp:protos */
#define RGP_SELF_TransMenuItemCellFocusCb_37f5c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct H37f5c0 {
    u8  pad00[0x18];
    void *f18;
} H37f5c0;

typedef struct G37f5c0 {
    u8  pad00[0x11];
    s8  f11;
} G37f5c0;

typedef struct T37f5c0 {
    u8  pad00[0x10];
    s16 f10;
    s16 f12;
} T37f5c0;

extern u8 D_004E9230[];
extern G37f5c0 *D_00484740;
extern f32 D_0047D240;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 TransMenuItemCellFocusCb_37f5c0(T37f5c0 *p)
{
    H37f5c0 *h;
    void *r;
    s32 a;
    s32 b;
    s32 n;
    s32 x;
    s32 y;
    s32 d;
    s32 t;
    u8 buf[16] __attribute__((aligned(16)));

    UiSelFrameSetGridCell_28db00(D_004E9230, 0x7604, p->f10, p->f12, 0x62, 0x49);
    h = ((H37f5c0 *)GetGameData_1fede0());
    y = p->f12;
    x = p->f10;
    d = D_00484740->f11;
    t = MenuGetMode_2a4e30(D_00484740);
    r = InvFindByCategoryIndex_3c86e0(h->f18, t, d, x, y, 0);
    n = -1;
    a = MenuGetSelMode_2a4e10(D_00484740);
    b = MenuGetMode_2a4e30(D_00484740);
    if (a == b) {
        n = p->f10 + p->f12 * 8;
    }
    TransMenuItemFetchWidgetRefs_37bdb0(buf);
    MenuItemInfoPopupShow_2a33e0(D_00484740, r, 0x762E, 0x762D, buf, 0x68, 0x15E, n, D_0047D240);
    return 1;
}
