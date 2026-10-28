/* rgp:protos */
#line 1
#include "types.h"
#pragma opt_propagation off

class Unit {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v21() { return VCM0(s32, 0x5C); }
    u8 pad004[0x8];
    s32 mC;
};

typedef struct {
    s16 x;
    s16 y;
} Pos;

typedef struct {
    u8 pad000[0xC];
    struct { u8 pad[0x26]; s16 m26; } *mC;
    u8 pad010[0x8];
    s32 m18;
} Party;

typedef struct {
    u8 pad000[0x6C];
    s8 m6C;
    u8 pad06D[3];
    f32 m70;
    s16 m74;
    s16 m76;
} Menu;

typedef struct {
    u8 pad000[0xE];
    s16 mE;
    u8 pad010[2];
    s16 m12;
    s16 m14;
    s16 m16;
    u8 pad018[2];
    s16 m1A;
} Win;

extern "C" {
extern s32 PadIsTriggered_1839f0(void *, s32);
extern void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
extern Party *GetGameData_1fede0(void);
extern f32 UiPageScrollBarLayout_289710(Menu *, s32, s32, s32, s32, s32);
extern Win *UiEntryListFindByTag_28ea40(s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void MenuSetMemberValueTextMaybe_3405a0(Menu *, s32);
extern void MenuCharaAbilityPageFill_3406a0(Menu *, s32, s32);
extern void MenuSetTabStyleMaybe_340a40(Menu *, s32, s32);
extern void PartyMenuCursorSet_3c0710(s32, s32, s16);
extern s32 PartyCountReserve_3c1c20(s32, s32, s32);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern Unit *PartyGetSlotChara_3c2fb0(s32, s32);
extern s32 PartyGetSlotId_3c3120(s32, s32);
extern void RevelationBoardRefreshMaybe_3eaec0(Party *, s32, s32);
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern Menu *D_00482378;
extern s32 D_0048238C;
extern s16 D_00482E20;
extern s16 D_00482E24;
extern s32 D_00482E34;
extern u8 D_004B2570[];
}

extern "C" void MenuRevelationBoardSwitchMember_348a40(void) {
    u8 *pad;
    Party *party;
    s32 h;
    s32 total;
    s32 old;
    s32 sel;
    s32 r;
    s16 *pos;
    Unit *u;
    Win *w1;
    Win *w2;
    Win *w3;
    s16 v;
    s32 z;
    Pos *dst;
    s16 px;
    s16 py;

    party = GetGameData_1fede0();
    if (party == 0) {
        return;
    }
    h = party->m18;
    total = PartyCountMembers_3c2010(h, 1, 1);
    total = total + PartyCountReserve_3c1c20(h, 1, 1);
    old = D_00482378->m6C;
    pad = D_004B2570;
    sel = old;
    if (PadIsTriggered_1839f0(pad, 4)) {
        sel--;
        if (sel < 0) {
            sel = total - 1;
        }
    } else if (PadIsTriggered_1839f0(pad, 8)) {
        sel++;
        if (sel >= total) {
            sel = 0;
        }
    }
    r = PartyGetSlotId_3c3120(party->m18, sel);
    if (r < 0 || r == 8) {
        return;
    }
    if (old != sel) {
        pos = (s16 *)(D_0048238C + 0x10);
        u = PartyGetSlotChara_3c2fb0(party->m18, old);
        if (u == 0) {
            return;
        }
        pad = (u8 *)(D_0048238C + 0x1C);
        RevelationBoardRefreshMaybe_3eaec0(party, u->v21(), (s32)pad);
        {
        s32 b_;
        py = pos[1];
        b_ = D_0048238C;
        dst = (Pos *)(u->mC * 4);
        px = pos[0];
        dst = (Pos *)((u8 *)dst + b_ + 0x780);
        }
        dst->x = px;
        dst->y = py;
        if (party->mC->m26 == 1) {
            z = 0;
            v = z | pos[0];
            v |= pos[1] << 8;
            PartyMenuCursorSet_3c0710(party->m18, u->mC + 7, v);
        }
        SoundPlayScaledVolume_1b9520(D_00482E34, 0xB, 0, 1.0f);
    }
    if (sel == D_00482378->m6C) {
        return;
    }
    if (PartyGetSlotChara_3c2fb0(party->m18, sel) == 0) {
        return;
    }
    UiSetWidgetPos_290f60(D_00482360, 0x18D, 0, 0);
    MenuSetTabStyleMaybe_340a40(D_00482378, 0x19B, sel);
    D_00482378->m6C = sel;
    MenuCharaAbilityPageFill_3406a0(D_00482378, sel, 0);
    MenuSetMemberValueTextMaybe_3405a0(D_00482378, sel);
    D_00482378->m70 = UiPageScrollBarLayout_289710(D_00482378, 0x19A, 0xA8, 6, D_00482378->m74, 0);
    UiSetWidgetPos_290f60(D_00482360, 0x19A, 0x180, 0x30);
    D_00482378->m76 = 0;
    w1 = UiEntryListFindByTag_28ea40(D_00482364, 0x19);
    w1->m1A = 0;
    w1->m16 = 0;
    w2 = UiEntryListFindByTag_28ea40(D_00482364, 0x19);
    if (D_00482378->m74 < 7) {
        w2->mE = D_00482378->m74 - 1;
    } else {
        w2->mE = 5;
    }
    w2->m12 = D_00482378->m74 - 1;
    w3 = UiEntryListFindByTag_28ea40(D_00482364, 0x17);
    w1->m14 = sel;
    w3->m14 = sel;
    D_00482378->m6C = sel;
    StateMachineSetState_28ede0(D_0048235C, 0xB4, 0);
    D_00482E20 = 0;
    D_00482E24 = 0;
}
