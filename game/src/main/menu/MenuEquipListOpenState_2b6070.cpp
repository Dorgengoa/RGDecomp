/* rgp:protos */
#line 1
#include "types.h"


class Lbl {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void Set(void * a0) { VCM(void, (void *, void *), 0x4C, a0); }
};
class Chr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 Get60() { return VCM0(s32, 0x60); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 GetE8() { return VCM0(s32, 0xE8); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Lbl * L388() { return VCM0(Lbl *, 0x388); }
    Lbl * L38C() { return VCM0(Lbl *, 0x38C); }
};

struct Sel { u8 pad[0x14]; s16 h14; s16 h16; };
struct Pg { u8 pad[0xA]; s16 hA; u8 padC[2]; s16 hE; };
struct Buf { s32 f0; u8 pad4[0x18]; s32 f1C; u8 pad20[0x90]; };

extern "C" {
void UiEntryListSelectByTag_28ea90(s32, s32, s32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, f32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
Sel *UiEntryListFindByTag_28ea40(s32, s32);
void MenuEquipCandidatesFill_29e290(s32, s32);
s32 MenuGetEquipCandidateCount_29e280(s32);
void MenuEquipCandidateGridRefresh_29e080(s32, s32, s32, s32);
s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
void UiLayoutPanelFrame_28d580(s32, s32, s32, s32, s32, s32);
void UiSetWidgetVisible_290010(s32, s32, s32, s32);
u8 *GetGameData_1fede0(void);
s32 MenuGetCursorIndex_29fa80(s32);
Chr *PartyGetSlotChara_3c2fb0(s32, s32);
void UiSetTextString_28f510(s32, s32, void *, s32);
s32 UiGetWidgetTextWidth_28f400(s32, s32, s32);
void UiSetTextX_28f590(s32, s32, s32, s32);
void *MsgTableLookup_28aa30(s32, s32);
void UiSetTextCenteredX_28f300(s32, s32, s32, s32);
void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
void MsgFormatParamsCtor_28aa00(Buf *);
void MsgFormat_28a9a0(void *, void *, Buf *, s32);
Pg *UiEntryListGetCurrentData_28ec60(s32);
f32 UiPageScrollBarLayout_289710(s32, s32, s32, s32, s32, s32);
void MenuSetScrollStep_29f990(s32, f32);
void UiSelFrameInit_28da30(void *, s32, s32);
void UiSelFrameSetRect_28db40(void *, s32, s32, s32, s32, s32, s32, s32);
void UiSelFrameCalcTileCounts_28d9d0(void *);
void UiSetWidgetAlpha_2907a0(s32, s32, f32);
s32 MenuGetEquipCandidate_29f9f0(s32, s32);
void MenuEquipCandidateInfoPanelUpdate_2b4360(s32);
void MenuSetGridSel_29f9b0(s32, s32, s32, s32);
void StateMachineSetState_28ede0(s32, s32, s32);
void UiSelFrameAnimStep_28d820(void *, s32);
}
extern "C" f32 D_0047D5BC;
extern "C" f32 D_0047D5D0;
extern "C" f32 D_0047D694;
extern "C" f32 D_0047D69C;
extern "C" f32 D_0047D6A0;
extern "C" s32 D_0048235C;
extern "C" s32 D_00482360;
extern "C" s32 D_00482364;
extern "C" s32 D_00482370;
extern "C" s32 D_004823D8;
extern "C" u8 D_004DB790[];
extern "C" u8 D_004DB7C0[];
extern "C" u8 D_004DB860[];
extern "C" u8 D_004DB8A0[];

extern "C" s32 MenuEquipListOpenState_2b6070(void *self, s32 on) {
    Buf buf __attribute__((aligned(16)));
    Sel *sel;
    s32 k;
    s32 t;
    Chr *c;
    Lbl *l;
    s32 w;
    s32 x;
    Pg *pg;

    if (on != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x15, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x133, 1, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x17E, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x17F, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x133, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x133, 0x200, 0x42);
        UiMoveWidgetUniform_290f50(D_00482360, 0x133, 0x42, 0x42, D_0047D694, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x133, 1.0f, D_0047D5D0, 0.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x17F, 0, 1);
        sel = UiEntryListFindByTag_28ea40(D_00482364, 0x13);
        k = sel->h14 + sel->h16 * 2;
        MenuEquipCandidatesFill_29e290(D_00482370, k);
        MenuEquipCandidateGridRefresh_29e080(D_00482370, 0x166, ((short)MenuGetEquipCandidateCount_29e280(D_00482370)), 0);
        if (sel->h16 == 0) {
            t = UiGetWidgetSprite_28fe10(D_00482360, 0x14F, 0);
            if (t == 0) return 0;
            UiLayoutPanelFrame_28d580(t, 0, 0, 0x1B1, 0xE6, 1);
            UiSetWidgetVisible_290010(D_00482360, 0x14F, 1, -1);
            UiSetWidgetPos_290f60(D_00482360, 0x14F, 0x42, 0xD0);
            UiFadeWidgetAlpha_290690(D_00482360, 0x14F, 1.0f, D_0047D69C, 0.0f);
            UiSetWidgetPos_290f60(D_00482360, 0x150, 0x20, 0x27);
            UiSetWidgetPos_290f60(D_00482360, 0x158, 0xE6, 0x27);
            UiSetWidgetVisible_290010(D_00482360, 0x151, 0, -1);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x152, 1, 1);
            UiSetWidgetPos_290f60(D_00482360, 0x152, 0x10, -0xE);
            c = PartyGetSlotChara_3c2fb0(*(s32 *)(GetGameData_1fede0() + 0x18), MenuGetCursorIndex_29fa80(D_00482370));
            if (k == 0) {
                l = c->L388();
            } else {
                l = c->L38C();
            }
            l->Set(D_004DB860);
            UiSetTextString_28f510(D_00482360, 0x150, D_004DB860, 0);
            w = 0x56 - UiGetWidgetTextWidth_28f400(D_00482360, 0x150, 0) / 2;
            if (w == -1) w = 0;
            UiSetTextX_28f590(D_00482360, 0x150, w, 0);
            UiSetWidgetPos_290f60(D_00482360, 0x181, 0x26, -0xA);
            UiSetTextString_28f510(D_00482360, 0x181, MsgTableLookup_28aa30(D_004823D8, 0x7D4), 0);
            UiSetTextCenteredX_28f300(D_00482360, 0x181, 0x50, 0);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x38, 1, 1);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x37, 1, 1);
            UiSetWidgetColor_2905b0(D_00482360, 0x37, 0.0f, 0.0f, 0.0f, D_0047D694);
            UiSetWidgetPos_290f60(D_00482360, 0x38, 0x14C, -0x28);
            UiSetWidgetPos_290f60(D_00482360, 0x37, 0x14F, -0x25);
            UiMoveWidgetUniform_290f50(D_00482360, 0x38, 0x14C, 0x12, D_0047D5D0, 0);
            UiMoveWidgetUniform_290f50(D_00482360, 0x37, 0x14F, 0x15, D_0047D5D0, 0);
            MsgFormatParamsCtor_28aa00(&buf);
            buf.f1C = c->Get60();
            buf.f0 = c->GetE8();
            MsgFormat_28a9a0(D_004DB8A0, MsgTableLookup_28aa30(D_004823D8, 0x7D3), &buf, 0);
            UiSetTextString_28f510(D_00482360, 0x38, D_004DB8A0, 0);
        }
        pg = UiEntryListGetCurrentData_28ec60(D_00482364);
        pg->hE = (((short)MenuGetEquipCandidateCount_29e280(D_00482370)) - 1) / 8;
        MenuSetScrollStep_29f990(D_00482370, UiPageScrollBarLayout_289710(D_00482370, 0x136, 0x5E, pg->hA + 1, pg->hE + 1, 0));
        UiSetWidgetPos_290f60(D_00482360, 0x136, 0x183, 0x1E);
        UiSelFrameInit_28da30(D_004DB7C0, D_00482360, 0x14E);
        UiSelFrameSetRect_28db40(D_004DB7C0, 0x14E, 0x19, 0x17, 0x2A, 0x30, 0x42, 0x42);
        UiSelFrameCalcTileCounts_28d9d0(D_004DB7C0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x185, 0.0f, D_0047D6A0, -1.0f);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x186, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x186, 1.0f, D_0047D5BC, -1.0f);
        UiSetWidgetPos_290f60(D_00482360, 0x186, 0x14, 0x3C);
        MenuEquipCandidateInfoPanelUpdate_2b4360(MenuGetEquipCandidate_29f9f0(D_00482370, 0));
        MenuSetGridSel_29f9b0(D_00482370, 0, 0, 0);
        UiSetWidgetPos_290f60(D_00482360, 0x165, 0, 0);
        UiSetWidgetPos_290f60(D_00482360, 0x134, 0, 0);
    }
    StateMachineSetState_28ede0(D_0048235C, 0x60, 0);
    UiSelFrameAnimStep_28d820(D_004DB7C0, 0x14E);
    UiSelFrameAnimStep_28d820(D_004DB790, 0x14D);
    return 1;
}
