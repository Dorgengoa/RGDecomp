#include "types.h"

typedef struct {
    u8 pad0[0x24];
    s16 unk24;
} C00354EC0;

typedef struct {
    u8 pad0[0xC];
    C00354EC0 *unkC;
} G00354EC0;

typedef struct {
    u8 pad0[0x12];
    s16 unk12;
} P00354EC0;

extern G00354EC0 *GetGameData_1fede0(void);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern P00354EC0 *UiEntryListGetCurrentData_28ec60(s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern f32 *UiGetWidgetColor_2904b0(s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(s32, s32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern s32 D_00462A40[];
extern f32 D_0047D35C;
extern f32 D_0047D5D0;
extern f32 D_0047D5F4;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_0048236C;
extern s32 D_00482F0C;
extern s16 D_00482F10;

s32 MenuTacticsModeOpenState_354ec0(s32 arg0, s32 arg1) {
    G00354EC0 *g;
    P00354EC0 *p;
    s32 i;
    s32 k;

    g = GetGameData_1fede0();
    if (g == NULL) {
        return 0;
    }
    if (arg1 != 0) {
        D_00482F0C = 0;
        D_00482F10 = 0;
        UiSetWidgetAlpha_2907a0(D_0048236C, 1, 0.0f);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x22, 1);
        p = UiEntryListGetCurrentData_28ec60(D_00482364);
        {
            s16 key = g->unkC->unk24;
            for (i = 0; i < 4; i++) {
                if (key == D_00462A40[i]) {
                    k = i * 25;
                    UiSetWidgetPos_290f60(D_0048236C, 2, 7, k + 6);
                    UiSetWidgetPos_290f60(D_0048236C, 4, -0x14, k + 2);
                    p->unk12 = i;
                    break;
                }
            }
        }
    }
    if (!(*UiGetWidgetColor_2904b0(D_00482360, 0xC6) < D_0047D35C)) {
        UiFadeWidgetAlpha_290690(D_00482360, 0xC6, 0.0f, D_0047D5F4, -1.0f);
    }
    if (UiGetWidgetAlpha_290770(D_00482360, 0xC6) <= 0.0f) {
        UiSetWidgetsVisibleById_291110(D_0048236C, 1, 1, 1);
        UiSetWidgetPos_290f60(D_0048236C, 1, 0xEA, 0xE9);
        UiFadeWidgetAlpha_290690(D_0048236C, 1, 1.0f, D_0047D5D0, -1.0f);
    }
    if (!(UiGetWidgetAlpha_290770(D_0048236C, 1) < 1.0f)) {
        StateMachineSetState_28ede0(D_0048235C, 0x9D, 0);
    }
    return 1;
}
