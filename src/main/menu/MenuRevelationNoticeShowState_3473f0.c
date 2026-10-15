#include "types.h"

extern s32 MsgTableLookup_28aa30(s32 a, s32 b);
extern void UiEntryListSelectByTag_28ea90(s32 a, s32 b, s32 c);
extern void StateMachineSetState_28ede0(s32 a, s32 b, s32 c);
extern void UiSetTextCenteredX_28f300(s32 a, s32 b, s32 c, s32 d);
extern void UiSetTextString_28f510(s32 a, s32 b, s32 c, s32 d);
extern void UiSetWidgetAlpha_2907a0(s32 a, s32 b, f32 c);
extern void UiSetWidgetPos_290f60(s32 a, s32 b, s32 c, s32 d);
extern void UiSetWidgetsVisibleById_291110(s32 a, s32 b, s32 c, s32 d);

extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_004823D8;

s32 MenuRevelationNoticeShowState_3473f0(s32 arg0, s32 arg1)
{
    (void) arg0;
    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x64, 1.0f);
        UiSetTextString_28f510(D_00482360, 0x64, MsgTableLookup_28aa30(D_004823D8, 0x103A), 0);
        UiSetTextCenteredX_28f300(D_00482360, 0x64, 0x79, 0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x64, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x64, 0x83, 0xDE);
    }
    StateMachineSetState_28ede0(D_0048235C, 0x77, 0);
    return 1;
}
