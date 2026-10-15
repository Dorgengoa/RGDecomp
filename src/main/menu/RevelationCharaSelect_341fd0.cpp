#include "types.h"

class VObj {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual s32 f21();
};

extern "C" {
s32 PadIsTriggered_1839f0(void *, s32);
void *GetGameData_1fede0(void);
s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
void MenuGridCursorRequestSe_28e9e0(s32, s32);
s32 UiEntryListFindByTag_28ea40(s32, s32);
void UiEntryListSelectByTag_28ea90(s32, s32, s32);
s32 UiEntryListGetCurrentData_28ec60(s32);
void StateMachineSetState_28ede0(s32, s32, s32);
s32 UiFindWidget_290460(s32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
void MenuWidgetPulseColor_340d40(s32, s32, s32);
void MenuPartyIconsMarkLearnableMaybe_340de0(s32, s32);
void MenuCycleCharaSel_341220(s32, s32);
VObj *PartyGetSlotChara_3c2fb0(s32, s32);
s32 PartyGetSlotId_3c3120(s32, s32);
void RevelationBoardRefreshMaybe_3eaec0(s32, s32, s32);
s32 WorldDataMgrNoRequestPending_3eef10(s32);
extern f32 D_0047D668;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482378;
extern s16 D_00482D04;
extern u8 D_004B2570[];
s32 RevelationCharaSelect_341fd0(s32 arg0, s32 arg1);
}

s32 RevelationCharaSelect_341fd0(s32 arg0, s32 arg1)
{
    s32 g;
    s32 e;
    s32 h;
    s32 q;
    s32 r;
    s32 m;
    s32 k;
    VObj *o;

    g = (s32)GetGameData_1fede0();
    if (arg1 != 0) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x47, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x4A, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x50, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x49, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x4B, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x48, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x5A, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x5C, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x5D, 0, 1);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x18, 0);
        e = UiEntryListFindByTag_28ea40(D_00482364, 0x18);
        *(s16 *)(e + 0x14) = *(s8 *)(D_00482378 + 0x6C);
        *(s16 *)(e + 0x1A) = 0;
        h = UiFindWidget_290460(D_00482360, 0x18C);
        if (h == 0) {
            return 0;
        }
        q = *(s32 *)(h + 0x20);
        if (q == 0) {
            return 0;
        }
        *(s16 *)(q + 8) = 0;
        *(s16 *)(q + 0xC) = 0x78;
        UiSetWidgetsVisibleById_291110(D_00482360, 0x18D, 0, 1);
        MenuPartyIconsMarkLearnableMaybe_340de0(D_00482378, 0x19C);
        D_00482D04 = 0;
    }
    MenuWidgetPulseColor_340d40(D_00482378, 0x19C, 0);
    if (D_00482D04 == 0) {
        r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 2, 0);
        m = UiEntryListGetCurrentData_28ec60(D_00482364);
        if (r == 2) {
            StateMachineSetState_28ede0(D_0048235C, 0x72, 0);
        } else if (PadIsTriggered_1839f0(D_004B2570, 0x1000) != 0) {
            MenuGridCursorRequestSe_28e9e0(D_00482364, 0);
            StateMachineSetState_28ede0(D_0048235C, 0x72, 0);
        } else if (PadIsTriggered_1839f0(D_004B2570, 0x4000) != 0) {
            if (*(s16 *)(D_00482378 + 0x74) > 0) {
                h = UiFindWidget_290460(D_00482360, 0x18C);
                if (h == 0) {
                    return 0;
                }
                q = *(s32 *)(h + 0x20);
                if (q == 0) {
                    return 0;
                }
                *(s16 *)(q + 8) = 0x78;
                *(s16 *)(q + 0xC) = 8;
                StateMachineSetState_28ede0(D_0048235C, 0x7B, 0);
                return 1;
            }
        } else if (r == 1) {
            k = PartyGetSlotId_3c3120(*(s32 *)(g + 0x18), *(s8 *)(D_00482378 + 0x6C));
            if (k >= 0 && k != 8 && *(s16 *)(m + 0x12) == 0) {
                D_00482D04 = 1;
            }
        } else if (PadIsTriggered_1839f0(D_004B2570, 0xC) != 0) {
            MenuCycleCharaSel_341220(m, 0);
        }
    }
    if (D_00482D04 != 0) {
        if (WorldDataMgrNoRequestPending_3eef10(*(s32 *)(g + 8)) != 0) {
            UiFadeWidgetAlpha_290690(D_00482360, 0x19E, 0.0f, D_0047D668, -1.0f);
            o = PartyGetSlotChara_3c2fb0(*(s32 *)(g + 0x18), *(s8 *)(D_00482378 + 0x6C));
            if (o == 0) {
                return 2;
            }
            RevelationBoardRefreshMaybe_3eaec0(g, o->f21(), 0);
            StateMachineSetState_28ede0(D_0048235C, 0x89, 0);
        }
    }
    return 1;
}
