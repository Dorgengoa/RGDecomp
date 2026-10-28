/* rgp:protos */
#line 1
#include "types.h"
#pragma opt_propagation off

struct Sub296 {
    u8 pad0[0x10];
    s16 *id;
};

struct Chr296 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Sub296 * a() { return VCM0(Sub296 *, 0x388); }
    Sub296 * b() { return VCM0(Sub296 *, 0x38C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    Sub296 * c() { return VCM0(Sub296 *, 0x3C4); }
    
    
    
    
    void d() { VCM0(void, 0x3D8); }
};

struct Ent296 {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
};

struct Cur296 {
    u8 pad0[0x6C];
    s32 x6C;
    s16 x70;
};

extern "C" {
u8 *UiEntryListFindByTag_28ea40(void *, s32);
u8 *GetGameData_1fede0(void);
void PartyMenuCursorSet_3c0710(s32, s32, s16);
s32 *GetSelectedInsectEntryMaybe_206ad0(void);
s32 InvFindInCategoryRange_3c8370(s32, s32, s32, s32, s32, s32);
s32 InvObjCastToItem4B0_3d3cd0(s32, int, int, int);
void UiSetWidgetsVisibleById_291110(void *, s32, s32, s32);
void TopMenuLayoutRows_296790(void);
void UiFadeWidgetAlpha_290690(void *, s32, f32, f32, f32);
Ent296 *GetMenuPartySnapshot_205870(void);
s32 PartyCountMembers_3c2010(s32, s32, s32);
u8 *GetCurrentScene_1f5be0(void);
s32 GetCharaResMgr_1fdb60(void);
s32 PartyGetSlotId_3c3120(s32, s32);
Chr296 *PartyFindCharaById_3c2ed0(s32, s32);
void CharaResReleaseWeapon1ById_1f0e60(s32, u8 *, s32);
void CharaResLoadWeapon1ById_1f0ee0(s32, s32, s32);
void CharaResReleaseWeapon2ById_1f0e20(s32, u8 *, s32);
void CharaResLoadWeapon2ById_1f0ea0(s32, s32, s32);
void CharaResReleasePcModelById_1f0de0(s32, u8 *, s32);
void CharaResLoadPcModelById_1f0f20(s32, s32, s32);
s32 GetActionMgr_1fdb50(void);
s32 ActionMgrFindById_233b50(s32, s32);
void CharaResetAim_212b90(s32, s32);
void FieldHudReshowMaybe_202d70(void);
void UiGetWidgetPos_2910a0(void *, s32, s32 *, s32 *);
void MainMenuPanelFadeOut_2968a0(void);
f32 UiGetWidgetAlpha_290770(void *, s32);
void WorkIconBuildPartyWeaponsMaybe_28dde0(void);
extern f32 D_0047D79C;
extern s16 D_0047EB98;
extern s32 D_0047EB9C;
extern s32 D_00482370;
extern Cur296 *D_00482374;
extern s16 D_00482390;
extern s16 D_004823A4;
extern s8 D_0048241C;
extern s16 D_00482420;
extern u8 D_004DB1B0[0x40];
extern u8 D_004DB1F0[0x40];
}

extern "C" s32 MenuCloseState_296380(s32 arg0, s32 arg1)
{
    u8 *g;
    s32 *p;
    s32 r;
    Ent296 *tbl;
    u8 *w;
    s32 m;
    s32 i;
    s32 id;
    Chr296 *c;
    Sub296 *sub;
    s32 ka;
    s32 kb;
    s32 kc;
    Ent296 *e;
    s32 x8;
    s32 xC;
    s32 first;
    u8 *gg;
    s32 obj;
    s32 sx;
    s32 sy;
    volatile s32 n;
    s32 v;
    u8 *w2;
    s32 cur;

    if (arg1 != 0) {
        D_00482390 = *(s16 *)(UiEntryListFindByTag_28ea40(D_004DB1F0, 1) + 0x16);
        g = GetGameData_1fede0();
        if (*(s16 *)(*(u8 **)(g + 0xC) + 0x26) == 1) {
            PartyMenuCursorSet_3c0710(*(s32 *)(g + 0x18), 0x15, D_00482390);
        }
        if (D_00482374 != 0 && D_00482374->x70 != 0) {
            p = GetSelectedInsectEntryMaybe_206ad0();
            p[0] = D_00482374->x6C;
            r = InvFindInCategoryRange_3c8370(*(s32 *)(g + 0x18), p[0], 0, -1, 0, 0);
            if (r != 0) {
                p[1] = InvObjCastToItem4B0_3d3cd0(r, 0, 0, 0);
            }
        }
        UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x41, 0, 1);
        UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x27, 0, 1);
        TopMenuLayoutRows_296790();
        UiFadeWidgetAlpha_290690(D_004DB1B0, 0x227, 0.0f, D_0047D79C, -1.0f);
        D_00482420 = 0;
        D_0047EB98 = 2;
        tbl = GetMenuPartySnapshot_205870();
        n = PartyCountMembers_3c2010(*(s32 *)(g + 0x18), 1, 1);
        w = GetCurrentScene_1f5be0();
        if (w == 0) {
            return 0;
        }
        m = GetCharaResMgr_1fdb60();
        if (m != 0 && D_00482370 != 0) {
            for (i = 0; i < n; i++) {
                id = PartyGetSlotId_3c3120(*(s32 *)(g + 0x18), i);
                c = PartyFindCharaById_3c2ed0(*(s32 *)(g + 0x18), id);
                sub = c->a();
                ka = -1;
                if (sub != 0) {
                    ka = *sub->id;
                }
                sub = c->b();
                kb = -1;
                if (sub != 0) {
                    kb = *sub->id;
                }
                sub = c->c();
                kc = -1;
                if (sub != 0) {
                    kc = *sub->id;
                }
                c->d();
                e = &tbl[id];
                x8 = e->x8;
                xC = e->xC;
                if (ka != e->x4) {
                    CharaResReleaseWeapon1ById_1f0e60(m, w, id);
                    CharaResLoadWeapon1ById_1f0ee0(m, id, ka);
                }
                if (kb != x8) {
                    CharaResReleaseWeapon2ById_1f0e20(m, w, id);
                    CharaResLoadWeapon2ById_1f0ea0(m, id, kb);
                }
                if (kc != xC) {
                    CharaResReleasePcModelById_1f0de0(m, w, id);
                    CharaResLoadPcModelById_1f0f20(m, id, kc);
                }
            }
        }
        gg = *(u8 **)(g + 0x18);
        first = tbl->x0;
        if (first != *(s16 *)(gg + 0x18E)) {
            obj = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), first);
            if (obj != 0) {
                CharaResetAim_212b90(obj, 0);
            }
            FieldHudReshowMaybe_202d70();
        }
    }
    UiGetWidgetPos_2910a0(D_004DB1B0, 0x16, &sx, &sy);
    if ((f32)sx <= -37.0f && D_00482420 == 0) {
        v = D_0047EB9C;
        w2 = GetCurrentScene_1f5be0();
        *(s32 *)(w2 + 0x4348) = *(s32 *)(w2 + 0x4344);
        *(s32 *)(w2 + 0x4344) = v;
        MainMenuPanelFadeOut_2968a0();
        D_00482420 = 1;
    }
    if (UiGetWidgetAlpha_290770(D_004DB1B0, 1) <= 0.0f) {
        WorkIconBuildPartyWeaponsMaybe_28dde0();
        if (D_00482374->x70 != 0) {
            D_004823A4 = 3;
        } else {
            D_004823A4 = 0;
        }
        D_0048241C = 0;
        cur = D_00482374->x6C;
        InvFindInCategoryRange_3c8370(*(s32 *)(GetGameData_1fede0() + 0x18), cur, 0, -1, 0, 0);
    }
    return 1;
}
