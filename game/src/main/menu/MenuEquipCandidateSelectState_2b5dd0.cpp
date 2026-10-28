/* rgp:protos */
#line 1
#include "types.h"

struct Info {
    u8 pad0[0x10];
    s16 h10;
    s16 h12;
    u8 pad14[2];
    s16 h16;
};

struct Sub {
    u8 pad0[4];
    s32 w4;
};

struct Tbl {
    u8 pad0[0xA0];
    s16 count;
    u8 padA2[2];
    s32 objs[64];
};

struct Mgr {
    u8 pad0[0x5C];
    Tbl tbl;
    u8 pad200[0x4CC - 0x200];
    Sub *p4CC;
};

extern "C" {
extern s32 MsgTableLookup_28aa30(s32, s32);
extern void UiSelFrameAnimStep_28d820(void *, s32);
extern s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern Info *UiEntryListGetCurrentData_28ec60(s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetTextString_28f510(s32, s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(s32, s32);
extern void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
extern void MenuPartyPanelsSetVisible_2b41c0(s32);
extern s32 ItemIsWeapon_3d46c0(s32);
extern s32 ItemCharaMeetsLevelReq_3d46f0(s32, s32, int, int);
extern s32 ItemFindOwnerChara_3d4d80(s32, s32);
extern f32 D_0047D69C;
extern f32 D_0047D6A0;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern Mgr *D_00482370;
extern s32 D_004823D8;
extern s16 D_00482554;
extern s16 D_0048255C;
extern s16 D_00482578;
extern u8 D_004B2570[];
extern u8 D_004DB790[];
extern u8 D_004DB7C0[];

s32 MenuEquipCandidateSelectState_2b5dd0(s32 arg0, s32 arg1)
{
    s32 v;
    s32 w;
    s32 res;
    Info *info;
    Mgr *m;
    s32 h;
    s32 idx;
    s32 obj;
    bool done;
    Tbl *tbl;
    f32 f;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x15, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x186, 1.0f, D_0047D69C, -1.0f);
        D_00482578 = 0;
    }
    UiGetWidgetPos_2910a0(D_00482360, 0x133, &v, &w);
    if (D_00482578 == 0 && v == 0x42) {
        D_00482578 = 1;
        MenuPartyPanelsSetVisible_2b41c0(0);
    }
    res = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 2, 0);
    info = UiEntryListGetCurrentData_28ec60(D_00482364);
    if (res == 2) {
        StateMachineSetState_28ede0(D_0048235C, 0x61, 0);
    } else if (res == 1) {
        m = D_00482370;
        if (m->p4CC->w4 != 0) {
            tbl = &m->tbl;
            h = info->h10;
            idx = h + info->h12 * 8 + info->h16 * 8;
            if (idx < m->tbl.count) {
                done = false;
                obj = tbl->objs[idx];
                if (ItemIsWeapon_3d46c0(obj) != 0 && ((unsigned char)ItemCharaMeetsLevelReq_3d46f0(obj, ItemFindOwnerChara_3d4d80(obj, 0), 0, 0)) == 0) {
                    UiSetTextString_28f510(D_00482360, 0x21E, MsgTableLookup_28aa30(D_004823D8, 0x7D2), 0);
                    D_00482554 = 0x60;
                    D_0048255C = 1;
                    StateMachineSetState_28ede0(D_0048235C, 0x4D, 0);
                    done = true;
                    UiFadeWidgetAlpha_290690(D_00482360, 0x186, 0.0f, D_0047D6A0, -1.0f);
                }
                if (!done) {
                    D_00482578 = 2;
                    UiEntryListSelectByTag_28ea90(D_00482364, 0x27, 0);
                    UiFadeWidgetAlpha_290690(D_00482360, 0x14F, 0.0f, D_0047D6A0, -1.0f);
                    UiFadeWidgetAlpha_290690(D_00482360, 0x151, 0.0f, D_0047D6A0, -1.0f);
                    MenuPartyPanelsSetVisible_2b41c0(1);
                }
            }
        }
    }
    f = UiGetWidgetAlpha_290770(D_00482360, 0x14F);
    if (D_00482578 == 2 && f <= 0.0f) {
        StateMachineSetState_28ede0(D_0048235C, 0x63, 0);
    }
    UiSelFrameAnimStep_28d820(D_004DB7C0, 0x14E);
    UiSelFrameAnimStep_28d820(D_004DB790, 0x14D);
    return 1;
}
}
