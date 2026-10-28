#include "types.h"

class VC2b7610 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f368() { return VCM0(s32, 0x368); }
    
    
    
    
    
    
    
    s32 f388() { return VCM0(s32, 0x388); }
    s32 f38C() { return VCM0(s32, 0x38C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f3C4() { return VCM0(s32, 0x3C4); }
    
    
    
    
    s32 f3D8() { return VCM0(s32, 0x3D8); }
};

struct O2b7610 {
    u8 pad0[0x18];
    s32 unk18;
};

struct E2b7610 {
    u8 pad0[0x14];
    s16 a;
    s16 b;
};

extern "C" {
O2b7610 *GetGameData_1fede0(void);
void UiSelFrameAnimStep_28d820(u8 *, s32);
s32 MenuGridCursorInput_28e170(s32, u8 *, s32, s32);
E2b7610 *UiEntryListFindByTag_28ea40(s32, s32);
void UiEntryListSelectByTag_28ea90(s32, s32, s32);
void UiEntryListGetCurrentData_28ec60(s32);
void GetGridCellPos_28ed30(u8 *, s32 *, s32 *);
void StateMachineSetState_28ede0(s32, s32, s32);
void UiSetWidgetVisible_290010(s32, s32, s32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
s32 MenuGetCursorIndex_29fa80(s32);
void MenuItemInfoPopupShow_2a33e0(s32, s32, s32, s32, u8 *, s32, s32, s32, f32);
void MenuItemInfoWidgetsCache_2b3f00(u8 *);
VC2b7610 *PartyGetSlotChara_3c2fb0(s32, s32);
extern f32 D_0047D5D0;
extern f32 D_0047D6B8;
extern f32 D_0047D6BC;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482370;
extern s32 D_00482374;
extern u8 D_004B2570[0x100];
extern u8 D_004DB790[0x100];

s32 MenuEquipSlotSelectState_2b7610(s32 arg0, s32 arg1) {
    s32 sp6C;
    s32 sp68;
    u8 sp50[0x18] __attribute__((aligned(16)));
    s32 r;
    E2b7610 *e;
    s32 k;
    O2b7610 *o;
    VC2b7610 *v;
    s32 t;

    r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 4, 0);
    UiEntryListGetCurrentData_28ec60(D_00482364);
    if (arg1 != 0) {
        UiSetWidgetVisible_290010(D_00482360, 0x14F, 0, -1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x133, 0, 1);
        e = UiEntryListFindByTag_28ea40(D_00482364, 0x13);
        k = e->a + e->b * 2;
        UiEntryListSelectByTag_28ea90(D_00482364, 0x13, 0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x185, 1, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x185, 1.0f, D_0047D6B8, -1.0f);
        GetGridCellPos_28ed30((u8 *)e + 4, &sp6C, &sp68);
        UiSetWidgetPos_290f60(D_00482360, 0x185, sp6C, sp68);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x14D, 1, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x14D, 1.0f, D_0047D6B8, -1.0f);
        o = GetGameData_1fede0();
        v = PartyGetSlotChara_3c2fb0(o->unk18, MenuGetCursorIndex_29fa80(D_00482370));
        if (k == 0) {
            t = v->f388();
        } else if (k == 1) {
            t = v->f38C();
        } else if (k == 2) {
            t = v->f3C4();
        } else if (k == 3) {
            t = v->f3D8();
        }
        MenuItemInfoWidgetsCache_2b3f00(sp50);
        MenuItemInfoPopupShow_2a33e0(D_00482374, t, 0x1AA, 0x1A9, sp50, 0x5D, 0x14A, -1, D_0047D5D0);
    }
    if (r == 2) {
        StateMachineSetState_28ede0(D_0048235C, 0x59, 0);
    } else if (r == 1) {
        k = MenuGetCursorIndex_29fa80(D_00482370);
        v = PartyGetSlotChara_3c2fb0(GetGameData_1fede0()->unk18, k);
        if (v->f368() == 0) {
            UiFadeWidgetAlpha_290690(D_00482360, 0x185, 0.0f, D_0047D6BC, -1.0f);
            StateMachineSetState_28ede0(D_0048235C, 0x5A, 0);
        }
    }
    UiSelFrameAnimStep_28d820(D_004DB790, 0x14D);
    return 1;
}
}
