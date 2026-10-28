#include "types.h"

typedef struct P { u8 pad[0x10]; s32 i10; } P;

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    void s10() { VCM0(void, 0x30); }
    
    void s12() { VCM0(void, 0x38); }
    
    void s14() { VCM0(void, 0x40); }
    
    void s16() { VCM0(void, 0x48); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void s32() { VCM0(void, 0x88); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    P * v388() { return VCM0(P *, 0x388); }
    P * v38C() { return VCM0(P *, 0x38C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    P * v3C4() { return VCM0(P *, 0x3C4); }
    
    
    
    
    P * v3D8() { return VCM0(P *, 0x3D8); }
};

typedef struct G { u8 pad[0x10]; s32 i10; u8 pad14[4]; s32 i18; } G;
typedef struct St { u8 pad[0x14]; s16 s14; s16 s16; } St;
typedef struct A { u8 pad[0x10]; s16 s10; s16 s12; } A;
typedef struct V { f32 x, y, z, w; } V;

extern "C" {
G *GetGameData_1fede0(void);
s32 MenuWeaponCmdListBuildMaybe_289c90(s32, s32, s32, s32);
void UiSelFrameAnimStep_28d820(void *, s32);
void UiSelFrameCalcTileCounts_28d9d0(void *);
void UiSelFrameInit_28da30(void *, s32, s32);
void UiSelFrameSetRect_28db40(void *, s32, s32, s32, s32, s32, s32, s32);
s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
St *UiEntryListFindByTag_28ea40(s32, s32);
A *UiEntryListGetCurrentData_28ec60(s32);
void StateMachineSetState_28ede0(s32, s32, s32);
s32 UiGetWidgetText_28f620(s32, s32, s32);
s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
void UiSetWidgetVisible_290010(s32, s32, s32, s32);
void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
void UiSetWidgetAlpha_2907a0(s32, s32, f32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
void MenuChoiceDim_29c130(s32, s32);
void MenuChoiceCursorSet_29c180(s32, s16, s32);
void UiHideWidgetIfFaded_29caf0(s32, s32);
s32 MenuGetCursorIndex_29fa80(s32);
void MenuDrawWeaponGrowth_2a0600(s32, s32, P *, s32, s32, s32, s32);
void MenuItemInfoPopupShow_2a33e0(s32, P *, s32, s32, V *, s32, s32, s32, f32);
void MenuItemInfoWidgetsCache_2b3f00(V *);
Obj *PartyGetSlotChara_3c2fb0(s32, s32);
s32 PartyGetSlotId_3c3120(s32, s32);
s32 StateFlagTest_3ccd70(s32, s32);
}
extern "C" f32 D_0047D5D0;
extern "C" f32 D_0047D6A0;
extern "C" f32 D_0047D6A4;
extern "C" f32 D_0047D6AC;
extern "C" f32 D_0047D6B0;
extern "C" s32 D_0048235C;
extern "C" s32 D_00482360;
extern "C" s32 D_00482364;
extern "C" s32 D_00482370;
extern "C" s32 D_00482374;
extern "C" s32 D_004823D8;
extern "C" u8 D_004B2570[];
extern "C" u8 D_004DB790[];
extern "C" u8 D_004DB7F0[];

extern "C" s32 MenuEquipSlotChoiceSelectState_2b6b20(s32 pad0, s32 init) {
    s32 r;
    A *a;
    St *st;
    G *g;
    s32 id;
    Obj *obj;
    P *p;
    s32 h;
    s32 q;
    s32 h2;
    V v70 __attribute__((aligned(16)));

    r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 4, 0);
    a = UiEntryListGetCurrentData_28ec60(D_00482364);
    st = UiEntryListFindByTag_28ea40(D_00482364, 0x13);
    if (init) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x12F, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x12F, 1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x185, 0.0f, D_0047D6A0, -1.0f);
        g = GetGameData_1fede0();
        id = MenuGetCursorIndex_29fa80(D_00482370);
        UiSetWidgetColor_2905b0(D_00482360, 0x130, 1.0f, 1.0f, 1.0f, 1.0f);
        UiSetWidgetColor_2905b0(D_00482360, 0x131, 1.0f, 1.0f, 1.0f, 1.0f);
        MenuChoiceCursorSet_29c180(D_00482370, a->s10, 1);
        obj = PartyGetSlotChara_3c2fb0(g->i18, id);
        if (st->s14 == 0 || st->s16 == 0) {
            MenuChoiceDim_29c130(D_00482370, 1);
            if (st->s14 == 0 && st->s16 == 0 && StateFlagTest_3ccd70(g->i10, 0xB6) != 0 && PartyGetSlotId_3c3120(g->i18, id) == 0) {
                MenuChoiceDim_29c130(D_00482370, 0);
            }
        } else {
            if (obj->v3D8() == 0) MenuChoiceDim_29c130(D_00482370, 1);
        }
        p = 0;
        if (st->s16 == 0) {
            if (st->s14 == 0) p = obj->v388();
            else if (st->s14 == 1) p = obj->v38C();
            MenuDrawWeaponGrowth_2a0600(D_00482374, D_00482360, p, 0x161, 0x157, 0x153, 0x15F);
            UiSetWidgetVisible_290010(D_00482360, 0x151, 1, -1);
            UiSetWidgetPos_290f60(D_00482360, 0x151, 0x50, 0x104);
            UiFadeWidgetAlpha_290690(D_00482360, 0x151, 1.0f, D_0047D6AC, 0.0f);
            UiSetWidgetPos_290f60(D_00482360, 0x152, 0, 0);
            q = p->i10;
            h = UiGetWidgetSprite_28fe10(D_00482360, 0x164, 0);
            if (h == 0) return 0;
            h2 = UiGetWidgetText_28f620(D_00482360, 0x164, 0);
            if (h2 == 0) return 0;
            if (MenuWeaponCmdListBuildMaybe_289c90(q, D_004823D8, h, h2) > 0) {
                UiSetWidgetsVisibleById_291110(D_00482360, 0x163, 1, 1);
                UiFadeWidgetAlpha_290690(D_00482360, 0x163, 1.0f, D_0047D6AC, 0.0f);
                UiSetWidgetPos_290f60(D_00482360, 0x163, 0xFC, 0xFE);
            }
            UiFadeWidgetAlpha_290690(D_00482360, 0x1A9, 0.0f, D_0047D6A4, -1.0f);
        } else if (st->s16 == 1) {
            if (st->s14 == 0) p = obj->v3C4();
            else if (st->s14 == 1) p = obj->v3D8();
            MenuItemInfoWidgetsCache_2b3f00(&v70);
            MenuItemInfoPopupShow_2a33e0(D_00482374, p, 0x1AA, 0x1A9, &v70, 0x5D, 0x14A, -1, D_0047D5D0);
        }
    }
    UiHideWidgetIfFaded_29caf0(D_00482370, 0x14F);
    UiHideWidgetIfFaded_29caf0(D_00482370, 0x133);
    if (r == 2) {
        UiFadeWidgetAlpha_290690(D_00482360, 0x163, 0.0f, D_0047D6B0, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0x5C, 0);
    } else if (r == 1) {
        st = UiEntryListFindByTag_28ea40(D_00482364, 0x13);
        g = GetGameData_1fede0();
        id = MenuGetCursorIndex_29fa80(D_00482370);
        switch (a->s12) {
        case 0:
            if (st->s14 != 0 || st->s16 != 0 || StateFlagTest_3ccd70(g->i10, 0xB6) == 0 || PartyGetSlotId_3c3120(g->i18, id) != 0) {
                UiSelFrameInit_28da30(D_004DB7F0, D_00482360, 0x180);
                UiSelFrameSetRect_28db40(D_004DB7F0, 0x180, 0xDA, 0x13, 0xBB, 0xB9, 0x42, 0xD0);
                UiSelFrameCalcTileCounts_28d9d0(D_004DB7F0);
                StateMachineSetState_28ede0(D_0048235C, 0x5E, 0);
            }
            break;
        case 1:
            if (st->s14 == 1 && st->s16 == 1) {
                obj = PartyGetSlotChara_3c2fb0(g->i18, id);
                if (obj == 0) return 0;
                if (obj->v3D8() != 0) StateMachineSetState_28ede0(D_0048235C, 0x5D, 0);
            }
            break;
        }
    }
    UiSelFrameAnimStep_28d820(D_004DB790, 0x14D);
    return 1;
}
