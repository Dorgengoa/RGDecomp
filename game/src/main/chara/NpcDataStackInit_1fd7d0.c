/* rgp:protos */
#define RGP_SELF_NpcDataStackInit_1fd7d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma peephole off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void strcpy(void *, void *);
extern u32 strlen(void *);
extern u8 D_0045BE70[0x400];
extern u8 D_0045BE90[0x400];
extern s32 D_0047E474;
extern u8 D_004B6920[0x400];
extern u8 D_004B69C0[0x400];
extern u8 D_004B8660[0x400];
extern u8 D_004B8700[0x400];

s32 NpcDataStackInit_1fd7d0(s32 arg0) {
    s32 temp_2;
    s32 temp_2_2;

    if (D_0047E474 >= 0) {
        return D_0047E474;
    }
    temp_2 = GetCurrentScene_1f5be0();
    temp_2_2 = RecStackPush_1c4240(temp_2, &(*(u8 *)D_0045BE90));
    D_0047E474 = temp_2_2;
    if (temp_2_2 < 0) {
        return -1;
    }
    MemStackHeapInit_14dee0(&(*(u8 *)D_004B6920), MemStackAllocAligned64_14da10(((s32)RecStackGetSlot_1c4330(temp_2, temp_2_2)), arg0), arg0);
    if (strlen(&(*(u8 *)D_0045BE70)) < 0x10U) {
        strcpy(&(*(u8 *)D_004B6920), &(*(u8 *)D_0045BE70));
    }
    MemStackHeapReinit_14de90(&(*(u8 *)D_004B6920));
    MemStackAlign64_14d8e0(&(*(u8 *)D_004B6920));
    MainCharaDataMemSetup_1edde0(&(*(u8 *)D_004B69C0), 1, &(*(u8 *)D_004B6920), arg0);
    (*(void * *)D_004B8660) = &(*(u8 *)D_004B6920);
    InsectCageMgrSetHeap_39b1a0(&(*(u8 *)D_004B8700), &(*(u8 *)D_004B6920));
    return D_0047E474;
}
