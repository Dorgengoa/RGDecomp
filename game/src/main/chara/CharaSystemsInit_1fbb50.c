/* rgp:protos */
#define RGP_SELF_CharaSystemsInit_1fbb50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

u32 strlen(const char *);
char *strcpy(char *, const char *);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern char D_0045BE60[];
extern char D_0045BE70[];
extern char D_0045BE80[];
extern s32 D_0047E474;
extern s32 D_00481A54;
extern s32 D_00481A58;
extern s32 D_00481A5C;
extern s32 D_00481A60;
extern s32 D_00481A64;
extern s32 D_00481A68;
extern s32 D_00481A6C;
extern s32 D_00481A70;
extern s32 D_00481A74;
extern s32 D_00481A78;
extern s32 D_00481A7C;
extern char D_004B6860[];
extern char D_004B68C0[];
extern char D_004B6920[];
extern s32 D_004B6980[];
extern s32 D_004B6984[];
extern s32 D_004B6988[];
extern s32 D_004B698C[];
extern s32 D_004B6990[];
extern s32 D_004B6994[];
extern s32 D_004B6998[];
extern s32 D_004B699C[];
extern s32 D_004B69A0[];
extern s32 D_004B69A4[];
extern s32 D_004B69A8[];
extern s32 D_004B69AC[];
extern s32 D_004B69B0[];
extern s32 D_004B69B4[];
extern u8 D_004B69C0[];
extern u8 D_004B7960[];
extern u8 D_004B8680[];
extern u8 D_004B86C0[];
extern u8 D_004B8700[];
extern u8 D_004B8800[];
extern u8 D_004B8820[];

void CharaSystemsInit_1fbb50(s32 arg0, s32 arg1) {
    u8 *a;
    u8 *b;
    u8 *c;
    s32 h;

    GetCurrentScene_1f5be0();
    MemStackClear_14dff0(D_004B6860);
    MemStackClear_14dff0(D_004B68C0);
    MemStackClear_14dff0(D_004B6920);
    D_0047E474 = -1;
    D_00481A54 = 0;
    D_00481A58 = 0;
    D_00481A60 = 0;
    D_00481A5C = 0;
    D_00481A64 = 0;
    D_00481A68 = 0;
    D_00481A6C = 0;
    D_00481A70 = 0;
    D_00481A74 = 0;
    D_00481A78 = 0;
    D_00481A7C = 0;
    CompassHudReset_371860(D_004B8800);
    D_004B6980[0] = 0;
    D_004B6984[0] = 0;
    D_004B6988[0] = 0;
    D_004B698C[0] = 0;
    D_004B6990[0] = 0;
    D_004B6994[0] = 0;
    D_004B6998[0] = 0;
    D_004B699C[0] = 0;
    D_004B69A0[0] = 0;
    D_004B69A4[0] = 0;
    D_004B69A8[0] = 0;
    D_004B69AC[0] = 0;
    D_004B69B0[0] = -1;
    D_004B69B4[0] = -1;
    FieldViewModeSetEntered_2f36d0(0);
    FieldViewModeSet_2f3590(-1);
    a = D_004B69C0;
    CharaDataMgrInit_1edf40(a);
    b = D_004B7960;
    CharaResMgrInit_1f2ed0(b);
    c = D_004B8680;
    ActionMgrInit_2348b0(c);
    AttackChainStateInitIdle_382f90(D_004B86C0);
    DamagePopupListReset_2d3230(((s32)GetDamagePopupList_2d9020()));
    InsectCageMgrReset_39b1e0(D_004B8700);
    if (arg0 != 0) {
        MemStackInit_14d810(D_004B6860, MemStackAllocAligned64_14da10(arg0, 0x30C00), 0x30C00);
        if (strlen(D_0045BE60) < 0x10) {
            strcpy(D_004B6860, D_0045BE60);
        }
        MemStackReset_14d830(D_004B6860);
        MemStackAlign64_14d8e0(D_004B6860);
        MainCharaDataMemSetup_1edde0(a, 0, D_004B6860, 0x30C00);
        if (strlen(D_0045BE70) < 0x10) {
            strcpy(D_004B6920, D_0045BE70);
        }
        MainCharaDataMemSetup_1edde0(a, 1, D_004B6920, 0x2CCCC);
        *(char **)(b + 0xD00) = D_004B6920;
        h = ((s32)GetBattleEffectPool_2d9030());
        BattleEffectPoolClear_2d3ef0(h);
        BattleEffectPoolAlloc_2d3cc0(h, 1, arg0, 0x10);
    }
    if (arg1 != 0) {
        MemStackHeapInit_14dee0(D_004B68C0, MemStackAllocAligned64_14da10(arg1, 0x4800), 0x4800);
        if (strlen(D_0045BE80) < 0x10) {
            strcpy(D_004B68C0, D_0045BE80);
        }
        MemStackHeapReinit_14de90(D_004B68C0);
        ActionMgrSetHeap_234900(c, D_004B68C0);
        ActionMgrSetSurfaceParams_233b30(c, D_004B8820);
    }
}
