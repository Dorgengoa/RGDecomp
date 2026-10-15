#include "types.h"
#pragma peephole off
#pragma no_branch_likely on
#pragma no_branch_likely off

extern s32 MemStackAlign64_14d8e0(s32);
extern s32 MemStackAllocAligned64_14da10(s32, s32);
extern s32 MemStackReturnToOwnerMaybe_14dad0(s32);
extern s32 MemStackHeapAlloc_14db10(s32, s32, s32, s32);
extern s32 MemStackHeapReinit_14de90(void *);
extern s32 MemStackHeapInit_14dee0(void *, s32, s32);
extern s32 MemStackClear_14dff0(void *);
extern s32 MapMgrSetHeap_1e33f0(s32, s32);
extern s32 MapMgrSetSkyHeap_1e3400(s32, s32);
extern s32 MapMgrInit_1e5830(s32);
extern s32 GetMapNodeFadeMaybe_201a10(void);
extern s32 GetMapNodeSpinFadeMaybe_201a20(void);
extern s32 GetMapSunLight_201a30(void);
extern s32 GetLensFlareMgr_201a40(void);
extern s32 GetMapSunaKemu_201a60(void);
extern s32 GetMinimapMgr_201a70(void);
extern s32 GetMapSequencer_201a80(void);
extern s32 GetMapMgr_201a90(void);
extern s32 GetMapHeap_201aa0(void);
extern s32 GetMapSkyHeap_201ab0(void);
extern s32 SunLightInit_293d70(s32);
extern s32 GetObjectDataHeap_2d1970(void);
extern s32 MapNodeFadeInitMaybe_2d9240(s32);
extern s32 MapNodeSpinFadeInitMaybe_2d93f0(s32);
extern s32 LensFlareInit_2ee1c0(s32);
extern s32 MapSequencerSetHeap_2fa440(s32, s32);
extern s32 MapSequencerInit_2fa450(s32);
extern s32 MinimapMgrInit_3222d0(s32);
extern s32 SunaKemuClear_33bb00(s32);
extern s32 strcpy(void *, void *);
extern u32 strlen(void *);
extern u8 D_0045C128[0x400];
extern u8 D_0045C130[0x400];
extern s8 D_00481AFC;
extern s32 D_00481B00;
extern s8 D_00481B04;
extern s32 D_00481B2C;
extern s8 D_00481B30;
extern s8 D_00481B34;
extern u8 D_004B8BB0[0x400];
extern u8 D_004B8C10[0x400];

void MapSystemsInit_2017f0(s32 arg0, s32 arg1) {
    s32 temp_2;
    s32 temp_2_2;

    MemStackClear_14dff0(&(*(s8 *)D_004B8BB0));
    MemStackClear_14dff0(&(*(s8 *)D_004B8C10));
    D_00481B30 = 0;
    D_00481B2C = -1;
    D_00481B00 = -1;
    D_00481B34 = 0;
    D_00481B04 = 0;
    temp_2 = GetMapMgr_201a90();
    MapMgrInit_1e5830(temp_2);
    MinimapMgrInit_3222d0(GetMinimapMgr_201a70());
    SunaKemuClear_33bb00(GetMapSunaKemu_201a60());
    D_00481AFC = 0;
    if (arg0 != 0) {
        MemStackHeapAlloc_14db10(arg0, 1, 0, 0x40);
        MemStackAlign64_14d8e0(arg0);
        MemStackHeapInit_14dee0(&(*(s8 *)D_004B8BB0), MemStackAllocAligned64_14da10(arg0, 0x3600), 0x3600);
        if (strlen(&(*(s8 *)D_0045C128)) < 0x10U) {
            strcpy(&(*(s8 *)D_004B8BB0), &(*(s8 *)D_0045C128));
        }
        MemStackHeapReinit_14de90(&(*(s8 *)D_004B8BB0));
        MemStackHeapInit_14dee0(&(*(s8 *)D_004B8C10), MemStackAllocAligned64_14da10(arg0, 0x54000), 0x54000);
        if (strlen(&(*(s8 *)D_0045C130)) < 0x10U) {
            strcpy(&(*(s8 *)D_004B8C10), &(*(s8 *)D_0045C130));
        }
        MemStackHeapReinit_14de90(&(*(s8 *)D_004B8C10));
        MemStackReturnToOwnerMaybe_14dad0(arg0);
        MapMgrSetSkyHeap_1e3400(temp_2, GetMapSkyHeap_201ab0());
        MapMgrSetHeap_1e33f0(temp_2, GetMapHeap_201aa0());
        temp_2_2 = GetMapSequencer_201a80();
        MapSequencerInit_2fa450(temp_2_2);
        MapSequencerSetHeap_2fa440(temp_2_2, GetObjectDataHeap_2d1970());
        if (arg1 != 0) {
            LensFlareInit_2ee1c0(GetLensFlareMgr_201a40());
            SunLightInit_293d70(GetMapSunLight_201a30());
            MapNodeSpinFadeInitMaybe_2d93f0(GetMapNodeSpinFadeMaybe_201a20());
            MapNodeFadeInitMaybe_2d9240(GetMapNodeFadeMaybe_201a10());
        }
    }
}
