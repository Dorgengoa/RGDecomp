#include "types.h"

typedef struct G_0037cdd0 {
    u8 pad0[0x40];
    s8 f40;
} G_0037cdd0;

extern void *D_00484710;
extern G_0037cdd0 *D_00484740;
extern void *D_0048470C;
extern f32 D_0047D978;
extern void UiFadeWidgetAlpha_290690(void *, s32, f32, f32, f32);
extern void StateMachineSetState_28ede0(void *, s32, s32);

s32 TransMenuItemQuantityCloseState_37cdd0(void *a, s32 b)
{
    s8 v;
    if (b != 0) {
        UiFadeWidgetAlpha_290690(D_00484710, 0x7613, 0.0f, D_0047D978, -1.0f);
    }
    v = D_00484740->f40;
    if (v == 1) {
        StateMachineSetState_28ede0(D_0048470C, 0x2B, 0);
    } else if (v == 2) {
        StateMachineSetState_28ede0(D_0048470C, 0x2E, 0);
    } else if (v == 3) {
        StateMachineSetState_28ede0(D_0048470C, 0x3E, 0);
    }
    return 1;
}
