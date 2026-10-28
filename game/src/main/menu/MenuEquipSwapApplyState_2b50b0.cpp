/* rgp:protos */
#line 1
#include "types.h"

typedef struct Mdl { u8 pad0[0x2C]; s16 m2C; } Mdl;
typedef struct Item { u8 pad0[0x10]; Mdl *mdl; } Item;
typedef struct Sub { u8 pad0[0xA4]; Item *items[1]; } Sub;
typedef struct Bat { u8 pad0[0x5C]; Sub sub; } Bat;
typedef struct Win { u8 pad0[0x14]; s16 m14; s16 m16; u8 pad18[2]; s16 m1A; } Win;
typedef struct Wld { u8 pad0[0x18]; s32 m18; } Wld;

class Chr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Item * g388() { return VCM0(Item *, 0x388); }
    Item * g38C() { return VCM0(Item *, 0x38C); }
    
    
    void s398(Item * a0) { VCM(void, (void *, Item *), 0x398, a0); }
    void s39C(Item * a0) { VCM(void, (void *, Item *), 0x39C, a0); }
    
    
    
    
    
    
    
    
    
    Item * g3C4() { return VCM0(Item *, 0x3C4); }
    void s3C8(Item * a0) { VCM(void, (void *, Item *), 0x3C8, a0); }
    
    
    
    Item * g3D8() { return VCM0(Item *, 0x3D8); }
    void s3DC(Item * a0) { VCM(void, (void *, Item *), 0x3DC, a0); }
};

extern "C" {
extern Wld *GetGameData_1fede0(void);
extern Win * UiEntryListFindByTag_28ea40(s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern s32 UiFindWidget_290460(s32, u16);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, u16, s32, s32);
extern void MenuPartyCharaIconsLayoutMaybe_29ad30(Bat *, s32, s16);
extern void MenuShowCharaStats_29bb00(Bat *, s32);
extern void MenuEquipCandidateGridRefresh_29e080(Bat *, s32, s32, s32);
extern s32 MenuGetEquipCandidateCount_29e280(Bat *);
extern void MenuSetPartyEquipIcon_29ec60(Bat *, s32, u16, s32);
extern void UiPlaceItemIconInQuadrant_29f720(Bat *, s32, s32, s32);
extern s32 MenuGetCursorIndex_29fa80(Bat *);
extern Chr *PartyGetSlotChara_3c2fb0(s32, s32);
extern void PartyGetSlotId_3c3120(s32, s32);
extern u16 D_0047ECE8[4];
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern Bat *D_00482370;
}

extern "C" s32 MenuEquipSwapApplyState_2b50b0(s32 arg0, s32 arg1)
{
    s32 id;
    u16 *tp;
    s32 k;
    Win *t;
    Item *nw;
    s32 r;
    Bat *bt;
    Wld *w;
    Item *it;
    s32 idx;
    Chr *c;
    Win *t2;
    Item **slot;
    Sub *sub;
    s32 m;

    if (arg1 != 0) {
        w = GetGameData_1fede0();
        id = MenuGetCursorIndex_29fa80(D_00482370);
        c = PartyGetSlotChara_3c2fb0(w->m18, id);
        t = UiEntryListFindByTag_28ea40(D_00482364, 0x15);
        bt = D_00482370;
        idx = t->m14 + t->m16 * 8 + t->m1A * 8;
        sub = &bt->sub;
        if (idx < *(s16 *)((u8 *)bt + 0xFC)) {
            t2 = UiEntryListFindByTag_28ea40(D_00482364, 0x13);
            k = t2->m14 + t2->m16 * 2;
            if (k == 0) {
                nw = c->g388();
            } else if (k == 1) {
                nw = c->g38C();
            } else if (k == 2) {
                nw = c->g3C4();
            } else if (k == 3) {
                nw = c->g3D8();
            }
            slot = &((Item **)((u8 *)sub + 0xA4))[idx];
            it = *slot;
            m = it->mdl->m2C;
            r = UiFindWidget_290460(D_00482360, D_0047ECE8[(u32)k]);
            UiPlaceItemIconInQuadrant_29f720(D_00482370, r, m, k);
            PartyGetSlotId_3c3120(w->m18, id);
            if (k == 0) {
                c->s398(it);
            } else if (k == 1) {
                c->s39C(it);
            } else if (k == 2) {
                c->s3C8(it);
            } else if (k == 3) {
                c->s3DC(it);
            }
            tp = &D_0047ECE8[k];
            MenuSetPartyEquipIcon_29ec60(D_00482370, id, *tp, k);
            *slot = nw;
            MenuEquipCandidateGridRefresh_29e080(D_00482370, 0x166, ((short)MenuGetEquipCandidateCount_29e280(D_00482370)), t->m1A);
            UiSetWidgetsVisibleById_291110(D_00482360, t->m14 + t->m16 * 8 + 0x166, 1, 1);
            UiSetWidgetsVisibleById_291110(D_00482360, *tp, 1, 1);
            MenuShowCharaStats_29bb00(D_00482370, id);
            MenuPartyCharaIconsLayoutMaybe_29ad30(D_00482370, 0xDB, id);
        }
    }
    UiSetWidgetsVisibleById_291110(D_00482360, 0x17E, 0, 1);
    UiSetWidgetsVisibleById_291110(D_00482360, 0x17F, 0, 1);
    UiSetWidgetPos_290f60(D_00482360, 0x17E, 0, 0);
    UiSetWidgetPos_290f60(D_00482360, 0x17F, 0, 0);
    StateMachineSetState_28ede0(D_0048235C, 0x61, 0);
    return 1;
}
