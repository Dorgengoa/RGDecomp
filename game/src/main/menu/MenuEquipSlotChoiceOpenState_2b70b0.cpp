#include "types.h"

class Chk {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v3D8() { return VCM0(s32, 0x3D8); }
};

typedef struct {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    u8 pad8[8];
    s16 unk10;
    s16 unk12;
} Ent;

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
    u8 pad14[4];
    s32 unk18;
} Glob;

extern "C" {
extern Glob *GetGameData_1fede0(void);
extern void UiLayoutStringGlyphs_28a800(s16 *, s32, s32, s32, s32);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern void UiSelFrameAnimStep_28d820(u8 *, s32);
extern Ent *UiEntryListFindByTag_28ea40(s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern Ent *UiEntryListGetCurrentData_28ec60(s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern s16 *UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetParent_2911a0(s32, s32, s32);
extern void MenuChoiceDim_29c130(s32, s32);
extern void MenuChoiceCursorSet_29c180(s32, s32, s32);
extern void MenuPartyWidgetToChoiceCell_29f510(s32, s32, Ent *);
extern s32 MenuGetCursorIndex_29fa80(s32);
extern Chk *PartyGetSlotChara_3c2fb0(s32, s32);
extern s32 PartyGetSlotId_3c3120(s32, s32);
extern s32 StateFlagTest_3ccd70(s32, s32);
extern f32 D_0047D6B4;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482370;
extern s32 D_004823D8;
extern u8 D_004DB790[];
}

extern "C" s32 MenuEquipSlotChoiceOpenState_2b70b0(s32 arg0, s32 arg1)
{
    Ent *t;
    s16 *p;
    Glob *g;
    s32 id;
    Ent *q;

    if (arg1 != 0) {
        t = UiEntryListGetCurrentData_28ec60(D_00482364);
        MenuPartyWidgetToChoiceCell_29f510(D_00482370, 0x12F, t);
        UiFadeWidgetAlpha_290690(D_00482360, 0x183, 1.0f, D_0047D6B4, -1.0f);
        UiSetWidgetColor_2905b0(D_00482360, 0x130, 1.0f, 1.0f, 1.0f, 1.0f);
        UiSetWidgetColor_2905b0(D_00482360, 0x131, 1.0f, 1.0f, 1.0f, 1.0f);
        UiSetWidgetVisible_290010(D_00482360, 0x151, 1, -1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x151, 0.0f);
        UiSetWidgetParent_2911a0(D_00482360, 0x183, 0x12F);
        UiSetWidgetParent_2911a0(D_00482360, 0x118, 0x12F);
        p = UiGetWidgetSprite_28fe10(D_00482360, 0x12F, 0);
        p[0x12] = 0x84;
        p[2] = 0x84;
        p[0x82] = 0x76;
        p[0x32] = 0x76;
        p[0xA2] = 0x82;
        p[0x90] = 0x82;
        p[0x40] = 0x82;
        p[0x60] = 0x87;
        p = UiGetWidgetSprite_28fe10(D_00482360, 0x130, 0);
        UiLayoutStringGlyphs_28a800(p, MsgTableLookup_28aa30(D_004823D8, 0x89C), 1, 0x47, -2);
        p = UiGetWidgetSprite_28fe10(D_00482360, 0x131, 0);
        UiLayoutStringGlyphs_28a800(p, MsgTableLookup_28aa30(D_004823D8, 0x89D), 1, 0x47, -2);
        q = UiEntryListFindByTag_28ea40(D_00482364, 0x14);
        UiSetWidgetPos_290f60(D_00482360, 0x183, q->unk4 - 0xE, q->unk6 - 4);
        MenuChoiceCursorSet_29c180(D_00482370, 0, 1);
        g = GetGameData_1fede0();
        id = MenuGetCursorIndex_29fa80(D_00482370);
        if (t->unk10 == 0 || t->unk12 == 0) {
            MenuChoiceDim_29c130(D_00482370, 1);
            if (t->unk10 == 0 && t->unk12 == 0 && StateFlagTest_3ccd70(g->unk10, 0xB6) != 0 && PartyGetSlotId_3c3120(g->unk18, id) == 0) {
                MenuChoiceDim_29c130(D_00482370, 0);
            }
        } else {
            if (PartyGetSlotChara_3c2fb0(g->unk18, id)->v3D8() == 0) {
                MenuChoiceDim_29c130(D_00482370, 1);
            }
        }
    }
    UiEntryListSelectByTag_28ea90(D_00482364, 0x14, 1);
    UiSelFrameAnimStep_28d820(D_004DB790, 0x14D);
    StateMachineSetState_28ede0(D_0048235C, 0x5B, 0);
    return 1;
}
