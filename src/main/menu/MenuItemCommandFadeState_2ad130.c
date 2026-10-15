#include "types.h"

typedef struct S_002ad130 {
    u8 pad0[0x40];
    s8 f40;
    u8 pad41;
    s16 f42;
} S_002ad130;

extern S_002ad130 *D_00482374;
extern s32 D_0048235C;
extern s32 D_00482364;
extern s32 D_00482360;
extern s8 D_0048249C;
extern s8 D_00482498;
extern f32 D_0047D710;
extern s32 MenuItemCmdFadeSequenceStep_2adce0(s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);

s32 MenuItemCommandFadeState_2ad130(void)
{
    S_002ad130 *s;
    s32 x;
    if (MenuItemCmdFadeSequenceStep_2adce0(0x85) == 0) goto one;
    s = D_00482374;
    x = s->f42;
    if (x == 0) {
        StateMachineSetState_28ede0(D_0048235C, 0x3C, 0);
    } else if (x == 1) {
        s->f40 = 1;
        D_0048249C = 0;
        StateMachineSetState_28ede0(D_0048235C, 0x33, 0);
    } else if (x == 2) {
        UiEntryListSelectByTag_28ea90(D_00482364, 3, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D710, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x78, 1.0f, D_0047D710, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 9, 0);
    } else if (x == 4) {
        D_00482498 = 2;
        StateMachineSetState_28ede0(D_0048235C, 0xB2, 0);
    } else if (x == 3) {
        s->f40 = 2;
        StateMachineSetState_28ede0(D_0048235C, 0x36, 0);
    }
one:
    return 1;
}
