/* rgp:protos */
#define RGP_SELF_MapSystemsInit_2017f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma peephole off
#pragma no_branch_likely on
#pragma no_branch_likely off

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
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
    temp_2 = ((s32)GetMapMgr_201a90());
    MapMgrInit_1e5830(temp_2);
    MinimapMgrInit_3222d0(((s32)GetMinimapMgr_201a70()));
    SunaKemuClear_33bb00(((s32)GetMapSunaKemu_201a60()));
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
        MapMgrSetSkyHeap_1e3400(temp_2, ((s32)GetMapSkyHeap_201ab0()));
        MapMgrSetHeap_1e33f0(temp_2, ((s32)GetMapHeap_201aa0()));
        temp_2_2 = ((s32)GetMapSequencer_201a80());
        MapSequencerInit_2fa450(temp_2_2);
        MapSequencerSetHeap_2fa440(temp_2_2, ((s32)GetObjectDataHeap_2d1970()));
        if (arg1 != 0) {
            LensFlareInit_2ee1c0(((s32)GetLensFlareMgr_201a40()));
            SunLightInit_293d70(((s32)GetMapSunLight_201a30()));
            MapNodeSpinFadeInitMaybe_2d93f0(((s32)GetMapNodeSpinFadeMaybe_201a20()));
            MapNodeFadeInitMaybe_2d9240(((s32)GetMapNodeFadeMaybe_201a10()));
        }
    }
}
