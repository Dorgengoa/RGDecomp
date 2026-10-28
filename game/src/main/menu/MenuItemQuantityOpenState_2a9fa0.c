/* rgp:protos */
#define RGP_SELF_MenuItemQuantityOpenState_2a9fa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R2A9 {
    u8  pad000[0x8];
    s16 m08;
    s16 m0A;
    u8  pad00C[0x8];
    s16 m14;
    s16 m16;
} R2A9;

extern void *D_00482360;
extern void *D_00482364;
extern void *D_0048235C;
extern f32 D_0047D6D0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuItemQuantityOpenState_2a9fa0(s32 a0, s32 flag)
{
    R2A9 *r;
    s32 h;
    s32 k;

    if (flag != 0) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x8A, 1, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x8A, 1.0f, D_0047D6D0, 0.0f);
        r = ((R2A9 *)UiEntryListFindByTag_28ea40(D_00482364, 0x3));
        h = r->m16;
        k = 0x4E;
        if (h == 4) {
            k = -0xA;
        }
        UiSetWidgetPos_290f60(D_00482360, 0x8A, r->m14 * r->m08 + 8, k + h * (r->m0A + 1));
    }
    StateMachineSetState_28ede0(D_0048235C, 0x41, 0);
    return 1;
}
