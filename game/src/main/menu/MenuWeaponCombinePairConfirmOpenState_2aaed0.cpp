#include "types.h"

typedef struct Mdl { u8 pad0[0x2C]; s16 m2C; } Mdl;
typedef struct Pos { u8 pad0[4]; s16 x; s16 y; } Pos;
typedef struct Bat { u8 pad0[0x2C]; s32 m2C; s32 m30; } Bat;
typedef struct Wld { u8 pad0[0x18]; s32 m18; } Wld;

class Chr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v04C(u8 * a0) { VCM(void, (void *, u8 *), 0x4C, a0); }
    u8 pad4[0xC];
    Mdl *mdl;
};

extern "C" {
extern u8 *MsgTableLookup_28aa30(s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern Pos *UiEntryListFindByTag_28ea40(s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetTextCenteredX_28f300(s32, s32, s32, s32);
extern void UiSetTextString_28f510(s32, s32, u8 *, s32);
extern void UiSetSpriteU_28f930(s32, s32, s32, s32);
extern u8 *UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void UiSetItemIconUv_288e50(u8 *, s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(s32, s32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern s32 UiWidgetIsMoving_290d30(s32, s32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern Chr *MenuGetSelItem_2a02d0(Bat *);
extern void MenuItemInfoPopupShow_2a33e0(Bat *, s32, s32, s32, u8 *, s32, s32, s32, f32);
extern void MenuItemInfoWidgetsCache_2a65f0(u8 *);
extern Wld *GetGameData_1fede0(void);
extern Chr *InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
extern void MenuWeaponCombineAnimTickMaybe_361cd0(s32);
extern void MenuWeaponCombineAutoHideTick_362700(s32);
extern f32 D_0047D470;
extern f32 D_0047D73C;
extern f32 D_0047D750;
extern s32 D_00481BBC;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern Bat *D_00482374;
extern s32 D_00482384;
extern s32 D_004823D8;
extern u8 D_004DB670[];
extern u8 D_004DB6B0[];
}

extern "C" s32 MenuWeaponCombinePairConfirmOpenState_2aaed0(s32 arg0, s32 arg1)
{
    u8 sp30[0x10] __attribute__((aligned(16)));
    Chr *c;
    u8 *p;
    Pos *q;
    s32 h;
    Wld *w;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x27, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 0.0f, D_0047D750, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x78, 0.0f, D_0047D750, -1.0f);
        MenuItemInfoWidgetsCache_2a65f0(sp30);
        MenuItemInfoPopupShow_2a33e0(D_00482374, 0, 0x1AA, 0x1A9, sp30, 0x68, 0x15E, -1, 2.0f);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x137, 0.0f);
        UiSetTextString_28f510(D_00482360, 0x139, MsgTableLookup_28aa30(D_004823D8, 0x461), 2);
        UiSetTextString_28f510(D_00482360, 0x139, MsgTableLookup_28aa30(D_004823D8, 0x462), 3);
        UiSetTextString_28f510(D_00482360, 0x139, MsgTableLookup_28aa30(D_004823D8, 0x463), 4);
        UiSetTextString_28f510(D_00482360, 0x139, MsgTableLookup_28aa30(D_00481BBC, 0x52), 5);
        UiSetTextString_28f510(D_00482360, 0x139, MsgTableLookup_28aa30(D_00481BBC, 0x53), 6);
        UiSetTextCenteredX_28f300(D_00482360, 0x139, 0x6A, 5);
        UiSetTextCenteredX_28f300(D_00482360, 0x139, 0xBA, 6);
    }
    if (UiWidgetIsMoving_290d30(D_00482360, 0x147) == 0) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x137, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x137, 0x96, 0x6E);
        UiFadeWidgetAlpha_290690(D_00482360, 0x137, 1.0f, D_0047D73C, -1.0f);
        w = GetGameData_1fede0();
        c = InvFindByCategoryIndex_3c86e0(w->m18, 0, (s32)(u32)D_00482374->m2C, D_00482374->m30 % 8, D_00482374->m30 / 8, 0);
        if (c == 0) {
            return 0;
        }
        c->v04C(D_004DB670);
        UiSetTextString_28f510(D_00482360, 0x139, D_004DB670, 0);
        p = UiGetWidgetSprite_28fe10(D_00482360, 0x13A, 0);
        if (p == 0) {
            return 0;
        }
        UiSetItemIconUv_288e50(p, c->mdl->m2C, 0x20, 0x20);
        c = MenuGetSelItem_2a02d0(D_00482374);
        if (c == 0) {
            return 0;
        }
        c->v04C(D_004DB6B0);
        UiSetTextString_28f510(D_00482360, 0x139, D_004DB6B0, 1);
        UiSetItemIconUv_288e50(p + 0x20, c->mdl->m2C, 0x20, 0x20);
        UiSetSpriteU_28f930(D_00482360, 0x139, 0x4C, 0);
        UiSetSpriteU_28f930(D_00482360, 0x139, 0x18, 1);
        q = UiEntryListFindByTag_28ea40(D_00482364, 0xC);
        UiSetWidgetPos_290f60(D_00482360, 0x13B, q->x, q->y);
    }
    if (!(UiGetWidgetAlpha_290770(D_00482360, 0x137) <= D_0047D470)) {
        StateMachineSetState_28ede0(D_0048235C, 0x21, 0);
    }
    h = D_00482384;
    MenuWeaponCombineAutoHideTick_362700(h);
    MenuWeaponCombineAnimTickMaybe_361cd0(h);
    return 1;
}
