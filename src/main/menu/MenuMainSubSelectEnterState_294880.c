#include "types.h"

extern void *GetGameData_1fede0(void);
extern void *UiEntryListFindByTag_28ea40(void *arg0, s32 arg1);
extern void StateMachineSetState_28ede0(void *arg0, s32 arg1, s32 arg2);
extern void UiSetWidgetVisible_290010(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void UiFadeWidgetAlpha_290690(void *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
extern void UiSetWidgetPos_290f60(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s16 PartyMenuCursorGet_3c0760(s32 arg0, s32 arg1);
extern f32 D_0047D790;
extern f32 D_0047D794;
extern u8 D_00482350;
extern void *D_00482360;
extern s16 D_00482394;
extern u8 D_004DB1B0[];
extern u8 D_004DB1F0[];

s32 MenuMainSubSelectEnterState_294880(s32 pd0, s32 arg1)
{
    u8 *g;
    u8 *t;

    g = GetGameData_1fede0();
    if (arg1 != 0) {
        UiSetWidgetVisible_290010(D_004DB1B0, 0x1AD, 1, -1);
        UiSetWidgetPos_290f60(D_004DB1B0, 0x1AD, 0x8E, 0x15A);
        UiFadeWidgetAlpha_290690(D_004DB1B0, 0x1AD, 1.0f, D_0047D790, 0.0f);
        UiFadeWidgetAlpha_290690(D_004DB1B0, 0x227, 0.0f, D_0047D794, -1.0f);
        t = UiEntryListFindByTag_28ea40(D_004DB1F0, 2);
        D_00482394 = 0;
        if (*(s16 *)(*(u8 **)(g + 0xC) + 0x26) == 1) {
            D_00482394 = PartyMenuCursorGet_3c0760(*(s32 *)(g + 0x18), 0x16);
            if (D_00482394 >= 2) {
                D_00482394 = 0;
            }
        }
        {
            s16 d = *(volatile s16 *)&D_00482394;
            *(s16 *)(t + 0x16) = d;
            UiSetWidgetPos_290f60(D_00482360, 0x1B2, *(s16 *)(t + 0x4), *(s16 *)(t + 0x6) + d * *(s16 *)(t + 0xA));
        }
    }
    StateMachineSetState_28ede0(&D_00482350, 6, 0);
    return 1;
}
