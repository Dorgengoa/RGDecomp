#include "types.h"

typedef struct R2A9 {
    u8  pad000[0x8];
    s16 m08;
    s16 m0A;
    u8  pad00C[0x8];
    s16 m14;
    s16 m16;
} R2A9;

extern void *D_00484710;
extern void *D_00484720;
extern void *D_0048470C;
extern f32 D_0047D970;

extern void UiSetWidgetsVisibleById_291110(void *p, s32 id, s32 a, s32 b);
extern void UiFadeWidgetAlpha_290690(void *p, s32 id, f32 x, f32 y, f32 z);
extern R2A9 *UiEntryListFindByTag_28ea40(void *p, s32 n);
extern void UiSetWidgetPos_290f60(void *p, s32 id, s32 a, s32 b);
extern void StateMachineSetState_28ede0(void *p, s32 id, s32 a);

s32 TransMenuItemQuantityOpenState_37d070(s32 a0, s32 flag)
{
    R2A9 *r;
    s32 h;
    s32 k;

    if (flag != 0) {
        UiSetWidgetsVisibleById_291110(D_00484710, 0x7613, 1, 1);
        UiFadeWidgetAlpha_290690(D_00484710, 0x7613, 1.0f, D_0047D970, 0.0f);
        r = UiEntryListFindByTag_28ea40(D_00484720, 0xB);
        h = r->m16;
        k = 0x4E;
        if (h == 4) {
            k = -0xA;
        }
        UiSetWidgetPos_290f60(D_00484710, 0x7613, r->m14 * r->m08 + 8, k + h * (r->m0A + 1));
    }
    StateMachineSetState_28ede0(D_0048470C, 0x28, 0);
    return 1;
}
