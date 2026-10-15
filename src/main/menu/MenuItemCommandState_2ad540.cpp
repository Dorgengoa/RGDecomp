#include "types.h"

typedef struct Pos {
    u8 pad0[0x8];
    s16 x8;
    s16 xA;
    u8 padC[0x8];
    s16 x14;
    s16 x16;
} Pos;

typedef struct Ent {
    s16 x0;
    s8 x2;
    u8 pad3[0x29];
    s16 x2C;
} Ent;

typedef struct Item {
    u8 pad0[0x4];
    s16 x4;
    u8 pad6[0x4];
    u8 xA;
    u8 padB[0x5];
    Ent *x10;
} Item;

typedef struct Menu {
    u8 pad0[0x11];
    s8 x11;
    u8 pad12[0x1A];
    s32 x2C;
    s32 x30;
    u8 pad34[0xE];
    s16 x42;
} Menu;

typedef struct Flags {
    u8 pad0[0x24C];
    u8 x24C;
    u8 pad24D[0x3];
    f32 x250;
} Flags;

typedef struct Game {
    u8 pad0[0x8];
    s32 x8;
    u8 padC[0xC];
    s32 x18;
    u8 pad1C[0x4];
    Flags *x20;
} Game;

typedef struct Cfg {
    u8 pad0[0x95];
    u8 x95;
} Cfg;

typedef struct Buf20 {
    u8 pad0[0x1C];
    s32 x1C;
    u8 pad20[0x90];
} Buf20;

class Obj {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual s32 V60();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual void d78();
    virtual void d79();
    virtual void d80();
    virtual void d81();
    virtual void d82();
    virtual void d83();
    virtual void d84();
    virtual void d85();
    virtual void d86();
    virtual void d87();
    virtual void d88();
    virtual void d89();
    virtual void d90();
    virtual void d91();
    virtual void d92();
    virtual void d93();
    virtual void d94();
    virtual void d95();
    virtual void d96();
    virtual void d97();
    virtual void d98();
    virtual void d99();
    virtual void d100();
    virtual void d101();
    virtual void d102();
    virtual void d103();
    virtual void d104();
    virtual void d105();
    virtual void d106();
    virtual void d107();
    virtual void d108();
    virtual void d109();
    virtual void d110();
    virtual void d111();
    virtual void d112();
    virtual void d113();
    virtual void d114();
    virtual void d115();
    virtual void d116();
    virtual void d117();
    virtual void d118();
    virtual void d119();
    virtual void d120();
    virtual void d121();
    virtual void d122();
    virtual void d123();
    virtual void d124();
    virtual void d125();
    virtual void d126();
    virtual void d127();
    virtual void d128();
    virtual void d129();
    virtual void d130();
    virtual void d131();
    virtual void d132();
    virtual void d133();
    virtual void d134();
    virtual void d135();
    virtual void d136();
    virtual void d137();
    virtual void d138();
    virtual void d139();
    virtual void d140();
    virtual void d141();
    virtual void d142();
    virtual void d143();
    virtual void d144();
    virtual void d145();
    virtual void d146();
    virtual void d147();
    virtual void d148();
    virtual void d149();
    virtual void d150();
    virtual void d151();
    virtual void d152();
    virtual void d153();
    virtual void d154();
    virtual s32 V274(s32);
    virtual void d156();
    virtual void d157();
    virtual void V280(void *);
    u8 pad4[0x8];
    s32 xC;
};

extern "C" {
extern s32 SoundNextPlayHandle_1b81c0(void);
extern void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
extern void SoundPlayDefault_1b9ae0(s32, s32, s32);
extern s32 GameSceneSoundSlot1GetHandle_1d07b0(s32);
extern s32 GetCurrentScene_1f5be0(void);
extern Game *GetGameData_1fede0(void);
extern void UiSetItemIconUv_288e50(s32, s32, s32, s32);
extern void PlayMenuSe_289ef0(s32);
extern void MsgFormat_28a9a0(void *, s32, Buf20 *, s32);
extern void MsgFormatParamsCtor_28aa00(Buf20 *);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern Pos *UiEntryListFindByTag_28ea40(s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetTextCenteredX_28f300(s32, s32, s32, s32);
extern void UiSetTextString_28f510(s32, s32, void *, s32);
extern s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiSetSpriteFlags_290bd0(s32, s32, s32, s32, s32, s32);
extern void UiMoveWidget_290e00(s32, s32, s32, s32, s32, f32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuMsgWindowSetSkin_295220(s32, s32);
extern Item *MenuGetSelItem_2a02d0(Menu *);
extern void MenuItemInfoPopupShow_2a33e0(Menu *, s32, s32, s32, void *, s32, s32, s32, f32);
extern void MenuItemInfoWidgetsCache_2a65f0(void *, s32);
extern s32 MenuWeaponCombineResultModelLoad_2a87c0(s32, s32);
extern s32 MenuItemCmdFadeSequenceStep_2adce0(s32);
extern void MenuItemUseFxCb_2ae7c0(void);
extern void MenuItemUseSeReset_2aea90(void);
extern void ItemUseMaybe_2eef60(s32, void *, void *, s32, u8 *);
extern void InsectCageSetTypeFromItem_391090(s32, s32);
extern void ExecInfoInitFromInvItem_3a7430(void *, s32, s32, s32);
extern void ExecInfoInit_3a7940(void *);
extern Obj *PartyGetLeaderChara_3c2820(s32);
extern void InvClearNewFlagsMaybe_3c3490(s32);
extern s32 WorldDataMgrNoRequestPending_3eef10(s32);
extern f32 D_0047D6D0;
extern f32 D_0047D718;
extern f32 D_0047D71C;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern Menu *D_00482374;
extern Cfg *D_00482384;
extern u8 D_00482398;
extern s16 D_004823B0;
extern s32 D_004823D8;
extern s32 D_004823E4;
extern u8 D_004DB560[];
}

extern "C" s32 MenuItemCommandState_2ad540(void) {
    u8 flag;
    u8 v180[0x1F];
    u8 buf[0x70];
    Buf20 v60;
    Game *g;
    Item *it;
    s32 k;
    Pos *q;
    Ent *p;
    s32 t;
    bool ok;
    Obj *o;
    s32 a;
    s32 x;
    s32 idx;
    s32 pos;
    s32 e;

    if (MenuItemCmdFadeSequenceStep_2adce0(0x83) == 0) {
        goto done;
    }
    g = GetGameData_1fede0();
    it = MenuGetSelItem_2a02d0(D_00482374);
    if (it == 0) {
        return 0;
    }
    k = D_00482374->x42;
    if (k == 3) {
        if (g->x20->x24C & 1) {
            D_004823B0 = 1000;
            StateMachineSetState_28ede0(D_0048235C, 4, 0);
        } else if (MenuWeaponCombineResultModelLoad_2a87c0(0, 3) != 0 && WorldDataMgrNoRequestPending_3eef10(g->x8) != 0 && D_00482398 != 0) {
            q = UiEntryListFindByTag_28ea40(D_00482364, 3);
            UiSetSpriteFlags_290bd0(D_00482360, 0x76, 0x208, 1, q->x14 + q->x16 * 8, 0);
            StateMachineSetState_28ede0(D_0048235C, 0x92, 0);
            UiEntryListSelectByTag_28ea90(D_00482364, 3, 0);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x36, 1, 1);
            UiSetWidgetPos_290f60(D_00482360, 0x36, 0x50, -0x26);
            UiSetTextString_28f510(D_00482360, 0x36, (void *)MsgTableLookup_28aa30(D_004823D8, 1000), 0);
            UiSetTextCenteredX_28f300(D_00482360, 0x36, 0xE8, 0);
            D_00482374->x2C = -1;
            D_00482374->x30 = -1;
            InvClearNewFlagsMaybe_3c3490(g->x18);
            SoundPlayDefault_1b9ae0(D_004823E4, 1, 0);
        }
    } else if (k == 0) {
        p = it->x10;
        if ((k=p->x2, t=*(s16 *)&p->x0, k == 0xE)) {
            MenuItemInfoWidgetsCache_2a65f0(v180, 3);
            MenuItemInfoPopupShow_2a33e0(D_00482374, 0, 0x1AA, 0x1A9, v180, 0x68, 0x15E, -1, 2.0f);
            StateMachineSetState_28ede0(D_0048235C, 0xA6, 0);
        } else if (t == 0x40D9 || (u32)(t - 0x40DE) < 2) {
            o = PartyGetLeaderChara_3c2820(g->x18);
            ok = true;
            if (t == 0x40D9) {
                if (g->x20->x24C & 1) {
                    D_004823B0 = 1000;
                    StateMachineSetState_28ede0(D_0048235C, 4, 0);
                    ok = false;
                } else if (!(g->x20->x250 <= 0.0f)) {
                    D_004823B0 = 1200;
                    StateMachineSetState_28ede0(D_0048235C, 4, 0);
                    ok = false;
                }
            } else if ((u32)(t - 0x40DE) < 2 && (g->x20->x24C & 1) && o->V274(-1) == 0) {
                D_004823B0 = 1100;
                StateMachineSetState_28ede0(D_0048235C, 4, 0);
                ok = false;
            }
            if (ok) {
                a = it->x4;
                ExecInfoInit_3a7940(buf);
                ExecInfoInitFromInvItem_3a7430(buf, o->xC, a, 0);
                o->V280(buf);
                flag = 0;
                MenuItemUseSeReset_2aea90();
                ItemUseMaybe_2eef60(-1, buf, (void *)MenuItemUseFxCb_2ae7c0, 0, &flag);
                if (flag == 0) {
                    PlayMenuSe_289ef0(6);
                }
                if (t == 0x40D9 && flag != 0) {
                    x = GameSceneSoundSlot1GetHandle_1d07b0(GetCurrentScene_1f5be0());
                    SoundPlayScaledVolume_1b9520(x, 0x4A, SoundNextPlayHandle_1b81c0(), 1.0f);
                    MenuMsgWindowSetSkin_295220(0x21E, 0);
                    MsgFormatParamsCtor_28aa00(&v60);
                    v60.x1C = o->V60();
                    MsgFormat_28a9a0(D_004DB560, MsgTableLookup_28aa30(D_004823D8, 0x44D), &v60, 1);
                    UiSetTextString_28f510(D_00482360, 0x21E, D_004DB560, 0);
                    StateMachineSetState_28ede0(D_0048235C, 0x3F, 0);
                } else {
                    StateMachineSetState_28ede0(D_0048235C, 9, 0);
                }
            }
        } else {
            o = PartyGetLeaderChara_3c2820(g->x18);
            if ((g->x20->x24C & 1) && o->V274(-1) == 0) {
                D_004823B0 = 1100;
                StateMachineSetState_28ede0(D_0048235C, 4, 0);
            } else {
                StateMachineSetState_28ede0(D_0048235C, 0x29, 0);
            }
        }
    } else if (k == 5) {
        if (g->x20->x24C & 1) {
            D_004823B0 = 1000;
            StateMachineSetState_28ede0(D_0048235C, 4, 0);
        } else {
            InsectCageSetTypeFromItem_391090(it->x10->x0, 3);
            StateMachineSetState_28ede0(D_0048235C, 0xAA, 0);
        }
    } else if (k == 1) {
        StateMachineSetState_28ede0(D_0048235C, 0x1D, 0);
    } else if (k == 2) {
        UiEntryListSelectByTag_28ea90(D_00482364, 3, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D718, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x78, 1.0f, D_0047D718, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 9, 0);
        if (it->xA & 1) {
            q = UiEntryListFindByTag_28ea40(D_00482364, 3);
            idx = D_00482374->x11;
            pos = q->x14 + q->x16 * 8;
            e = UiGetWidgetSprite_28fe10(D_00482360, 0x147, 0);
            if (e == 0) {
                return 0;
            }
            UiSetItemIconUv_288e50(e, it->x10->x2C, 0x28, 0x2D);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x147, 1, 1);
            UiSetWidgetPos_290f60(D_00482360, 0x147, (s32)(98.0f + (f32)(q->x14 * q->x8)), (s32)(73.0f + (f32)(q->x16 * q->xA)));
            UiMoveWidget_290e00(D_00482360, 0x147, 0x2D, 0x12C, 3, D_0047D6D0, 0.0f);
            UiFadeWidgetAlpha_290690(D_00482360, 0x147, 0.0f, D_0047D71C, 1.0f);
            UiSetSpriteFlags_290bd0(D_00482360, 0x76, 0x208, 1, pos, 0);
            if (D_00482384->x95 == 2) {
                D_00482374->x2C = idx;
                D_00482374->x30 = pos;
                UiEntryListSelectByTag_28ea90(D_00482364, 0x27, 0);
                UiFadeWidgetAlpha_290690(D_00482360, 0x227, 0.0f, D_0047D718, -1.0f);
                UiFadeWidgetAlpha_290690(D_00482360, 0x78, 0.0f, D_0047D718, -1.0f);
            } else if (D_00482384->x95 == 4) {
                StateMachineSetState_28ede0(D_0048235C, 0x20, 0);
            }
            SoundPlayDefault_1b9ae0(D_004823E4, 3, 0);
        }
    }
done:
    return 1;
}
