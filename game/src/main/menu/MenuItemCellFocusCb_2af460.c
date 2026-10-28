/* rgp:protos */
#define RGP_SELF_MenuItemCellFocusCb_2af460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj {
    u8 pad0[0x10];
    s16 x10;
    s16 x12;
} Obj;

typedef struct G {
    u8 pad0[0x18];
    s32 x18;
} G;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00482360;
extern s32 D_00482374;
extern u8 D_004B2570[0x400];

s32 MenuItemCellFocusCb_2af460(Obj *arg0)
{
    u8 buf[0x10] __attribute__((aligned(16)));
    G *g;
    s32 k;
    s32 r;

    if (PadIsTriggered_1839f0(D_004B2570, 0x2000) != 0) {
        if (arg0->x10 == 1 && arg0->x12 == 0) {
            arg0->x12 = 1;
        }
    }
    if (arg0->x12 == 0) {
        arg0->x10 = 0;
        UiSetWidgetPos_290f60(D_00482360, 0x70, 0x115, 0x51);
    } else if (arg0->x12 == 1) {
        UiSetWidgetPos_290f60(D_00482360, 0x70, arg0->x10 * 100 + 0xE3, 0xA1);
    }
    g = ((G *)GetGameData_1fede0());
    k = arg0->x10 + arg0->x12 - 1;
    if (k < 0) {
        k = 2;
    }
    r = ((s32)InvFindByCategoryIndex_3c86e0(g->x18, 3, 0, k, 0, 0));
    MenuItemInfoWidgetsCache_2a65f0(buf);
    MenuItemInfoPopupShow_2a33e0(D_00482374, r, 0x1AA, 0x1A9, buf, 0x68, 0x15E, -1, 2.0f);
    return 1;
}
