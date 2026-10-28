/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3

class Chr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f60() { return VCM0(s32, 0x60); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f398(u8 * a0) { VCM(void, (void *, u8 *), 0x398, a0); }
    void f39C(u8 * a0) { VCM(void, (void *, u8 *), 0x39C, a0); }
    
    
    
    
    
    
    
    
    
    
    void f3C8(u8 * a0) { VCM(void, (void *, u8 *), 0x3C8, a0); }
};

extern "C" {
s32 DoubleLess_1002b0(double, double);
s32 PadIsTriggered_1839f0(u8 *, s32);
void PlayMenuSe_289ef0(s32);
s32 MsgTableLookup_28aa30(s32, s32);
void UiSelFrameAnimStep_28d820(u8 *, s32);
s32 MenuGridCursorInput_28e170(s32, u8 *, s32, s32);
s32 UiEntryListFindByTag_28ea40(s32, s32);
void UiEntryListSelectByTag_28ea90(s32, s32, s32);
void UiEntryListGetCurrentData_28ec60(s32);
void StateMachineSetState_28ede0(s32, s32, s32);
void UiSetTextString_28f510(s32, s32, s32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
f32 UiGetWidgetAlpha_290770(s32, s32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
void MenuSetTitleFmtMaybe_2a3f40(u8 *, s32);
void MenuItemGridMarkInUse_2a4860(u8 *, s32);
u8 *MenuGetItemAtCell_2a7000(s32, s32);
void MenuCursorBobUpdate_2a9c00(void);
void MenuSetToggle_2b3a20(s32, long long);
s32 ItemCharaMeetsLevelReq_3d46f0(u8 *, Chr *, int, int);
Chr *ItemFindOwnerChara_3d4d80(u8 *, s32);
double fptodp(f32);
extern s64 D_0047D188;
extern f32 D_0047D6D0;
extern f32 D_0047D6F8;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern u8 *D_00482374;
extern s32 D_004823D8;
extern s8 D_004824CC;
extern u8 D_004B2570[];
extern u8 D_004DB430[];
s32 MenuItemGridInfoState_2a96c0(void);
}

s32 MenuItemGridInfoState_2a96c0(void) {
    u8 *p2;
    s32 r;
    s8 t;
    u8 *p;
    Chr *o;

    r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
    UiEntryListGetCurrentData_28ec60(D_00482364);
    if (r == 1) {
        if (D_004824CC == 0) {
            UiFadeWidgetAlpha_290690(D_00482360, 0xA4, 0.0f, D_0047D6F8, -1.0f);
            UiEntryListSelectByTag_28ea90(D_00482364, 0x27, 0);
            { s32 v = UiEntryListFindByTag_28ea40(D_00482364, 3); p = MenuGetItemAtCell_2a7000(*(s8 *)(D_00482374 + 0x11), v + 4); }
            if (p == 0) {
                return 0;
            }
            if (((unsigned char)ItemCharaMeetsLevelReq_3d46f0(p, ItemFindOwnerChara_3d4d80(p, 0), 0, 0)) == 0) {
                UiSetTextString_28f510(D_00482360, 0x21E, MsgTableLookup_28aa30(D_004823D8, 0x7D2), 0);
                StateMachineSetState_28ede0(D_0048235C, 0x3F, 0);
                UiFadeWidgetAlpha_290690(D_00482360, 0x227, 0.0f, D_0047D6F8, -1.0f);
            }
        } else if (D_004824CC == 1 || D_004824CC == 2) {
            StateMachineSetState_28ede0(D_0048235C, 0x45, 0);
        }
    } else if (r == 2) {
        StateMachineSetState_28ede0(D_0048235C, 0x45, 0);
    } else if (D_004824CC != 2) {
        if (PadIsTriggered_1839f0(D_004B2570, 0x2000) != 0) {
            MenuSetToggle_2b3a20(0xA5, (long long)(1));
        } else if (PadIsTriggered_1839f0(D_004B2570, 0x8000) != 0) {
            MenuSetToggle_2b3a20(0xA5, (long long)(0));
        }
    }
    if (D_004824CC != 2 && ((unsigned char)DoubleLess_1002b0(fptodp(UiGetWidgetAlpha_290770(D_00482360, 0xA4)), __builtin_bit_cast(double, (long long)(D_0047D188)))) != 0) {
        { s32 v = UiEntryListFindByTag_28ea40(D_00482364, 3); p2 = MenuGetItemAtCell_2a7000(*(s8 *)(D_00482374 + 0x11), v + 4); }
        if (p2 == 0) {
            return 0;
        }
        o = ItemFindOwnerChara_3d4d80(p2, 0);
        MenuSetTitleFmtMaybe_2a3f40(D_00482374, o->f60());
        t = *(s8 *)(*(u8 **)(p2 + 0x10) + 2);
        if (t == 0) {
            o->f398(p2);
        } else if (t == 1) {
            o->f39C(p2);
        } else if (t == 2) {
            o->f3C8(p2);
        }
        UiSetWidgetsVisibleById_291110(D_00482360, 0xB4, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0xB4, 0x89, 0xB4);
        UiFadeWidgetAlpha_290690(D_00482360, 0xB4, 1.0f, D_0047D6D0, 0.0f);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
        PlayMenuSe_289ef0(9);
        MenuItemGridMarkInUse_2a4860(D_00482374, 0x74);
        D_004824CC = 2;
    }
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    if (D_004824CC != 2) {
        MenuCursorBobUpdate_2a9c00();
    }
    return 1;
}
