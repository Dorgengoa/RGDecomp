#include "types.h"

typedef struct {
    u8 pad0[0x26];
    s16 x26;
} Sub;

typedef struct {
    u8 pad0[0x24C];
    u8 x24C;
} Sub2;

typedef struct {
    u8 pad0[0xC];
    Sub *xC;
    s32 x10;
    s32 pad14;
    s32 x18;
    s32 pad1C;
    Sub2 *x20;
} Ctx;

extern void MemStackReset_14d830(s32);
extern s32 MemStackNew_14e1b0(s32, s32);
extern void *GetCurrentScene_1f5be0(void);
extern Ctx *GetGameData_1fede0(void);
extern void MenuSetLeaderSlot_205880(s32);
extern s32 GetMenuReadBufStack_206a90(void);
extern s32 GetMenuCapStack_206ab0(void);
extern s32 GetMenuMainStack_206ac0(void);
extern void *GetSelectedInsectEntryMaybe_206ad0(void);
extern s32 SceneSoundGetSlot0HandleCur_207df0(void);
extern void MenuModelStateClear_294540(void);
extern void MenuOpeningPanelSetupMaybe_298600(void);
extern void MenuCaptureScreenTex_298810(void);
extern void MenuMainResLoad_299080(void);
extern void MainMenuAllocIconMaskClut_2994e0(void);
extern void DebugItemListInit_29a2a0(void *);
extern void DebugItemIconGridInit_29a2d0(void *);
extern void MenuWeaponCombineResultModelInit_2a89c0(void);
extern void MenuCageNoticeIdxReset_2b30c0(void);
extern u8 CharaIsPartyLeader_3ae1a0(void *);
extern s16 PartyMenuCursorGet_3c0760(s32, s32);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern void *PartyGetMemberChara_3c2420(s32, s32);
extern u8 StateFlagTest_3ccd70(s32, s32);
extern s16 D_0047EB90;
extern s16 D_0047EB94;
extern s16 D_0047EB98;
extern s32 D_0047EB9C;
extern s32 D_00482330;
extern s32 D_00482334;
extern s32 D_00482338;
extern s32 D_0048233C;
extern s16 D_00482344;
extern volatile s16 D_00482390;
extern s8 D_00482398;
extern s16 D_0048239C;
extern s16 D_004823A0;
extern s16 D_004823A4;
extern s16 D_004823A8;
extern s16 D_004823AC;
extern s16 D_004823B0;
extern s8 D_004823B4;
extern s8 D_004823CC;
extern s32 D_004823D8;
extern s32 D_004823DC;
extern s32 D_004823E0;
extern s8 D_004823E8;
extern s8 D_004823EC;
extern s8 D_004823F0;
extern s32 D_004823F8;
extern s32 D_00482410;
extern s8 D_0048241C;
extern u8 D_004DB220[0x400];
extern u8 D_004DB240[0x400];

void MenuSysInitMaybe_297640(void)
{
    Ctx *c;
    s32 i;
    s16 k;
    u32 n;
    u8 *e;
    s32 t;
    u8 *w;

    w = (u8 *)GetSelectedInsectEntryMaybe_206ad0();
    *(s32 *)(w + 0x0) = 0;
    *(s32 *)(w + 0x4) = 0;
    D_004823E8 = 0;
    D_0047EB9C = *(s32 *)((u8 *)GetCurrentScene_1f5be0() + 0x4344);
    MenuModelStateClear_294540();
    D_004823CC = 0;
    D_00482330 = SceneSoundGetSlot0HandleCur_207df0();
    D_00482334 = GetMenuMainStack_206ac0();
    D_00482338 = GetMenuReadBufStack_206a90();
    MemStackReset_14d830(D_00482338);
    D_0048233C = GetMenuCapStack_206ab0();
    MainMenuAllocIconMaskClut_2994e0();
    MenuCageNoticeIdxReset_2b30c0();
    MenuCaptureScreenTex_298810();
    MenuWeaponCombineResultModelInit_2a89c0();
    D_004823AC = 0;
    D_00482410 = 0;
    D_0048239C = 0;
    D_004823EC = 0;
    D_004823B4 = 0;
    D_00482398 = 0;
    c = GetGameData_1fede0();
    if (c != NULL) {
        k = 3;
        if (c->x20->x24C & 1) {
            k = 3;
        }
        D_004823F8 = MemStackNew_14e1b0(k * 0x38, D_00482334);
        MenuMainResLoad_299080();
        D_004823A0 = 0;
        D_004823F0 = 0;
        D_0048241C = t = StateFlagTest_3ccd70(c->x10, 0x7F8);
        D_00482390 = 0;
        if (c->xC->x26 == 1 && t == 0) {
            k = PartyMenuCursorGet_3c0760(c->x18, 0x15);
            D_00482390 = k;
            if (k > 7) {
                D_00482390 = 0;
            }
        }
        D_004823B0 = 0;
        D_004823A8 = 1;
        D_004823A4 = 1;
        D_0047EB98 = 1;
        D_004823B4 = 0;
        D_00482344 = D_00482390;
        n = PartyCountMembers_3c2010(c->x18, 1, 1);
        for (i = 0; i < (s32)n; i++) {
            e = (u8 *)PartyGetMemberChara_3c2420(c->x18, i);
            if (CharaIsPartyLeader_3ae1a0(e) == 1) {
                D_0047EB90 = *(s32 *)(e + 0xC);
                D_0047EB94 = i;
                MenuSetLeaderSlot_205880(i);
            }
        }
        D_004823D8 = 0;
        D_004823E0 = 0;
        D_004823DC = 0;
        DebugItemListInit_29a2a0(D_004DB220);
        DebugItemIconGridInit_29a2d0(D_004DB240);
        MenuOpeningPanelSetupMaybe_298600();
    }
}
