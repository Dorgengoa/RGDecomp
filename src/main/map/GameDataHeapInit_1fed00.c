#include "types.h"

extern s32 Memalign_130ba8(s32, s32);
extern void MemStackInit_14d810(void *, s32, s32);
extern void MemStackReset_14d830(void *);
extern void MemStackClear_14dff0(void *);
extern s32 GetGameData_1fede0(void);
extern s32 GetWorldDataMgr_1fedf0(void);
extern s32 GameDataStackSize_202620(void);
extern void GameDataCreate_3ee1f0(s32, void *);
extern void WorldDataMgrInit_3f3060(s32, void *);
extern char *strcpy(char *, const char *);
extern u32 strlen(const char *);
extern u8 D_0045BEB0[0x400];
extern u8 D_004B8A20[0x400];

s32 GameDataHeapInit_1fed00(void) {
    s32 temp_2_2;
    s32 temp_2;
    s32 temp_17;
    s32 temp_16;

    temp_2 = GameDataStackSize_202620();
    temp_2_2 = Memalign_130ba8(0x10, temp_2 * 0x10);
    if (temp_2_2 == 0) {
        return 0;
    }
    MemStackClear_14dff0(&(*(u8 *)D_004B8A20));
    MemStackInit_14d810(&(*(u8 *)D_004B8A20), temp_2_2, temp_2);
    if (strlen((char *) &(*(u8 *)D_0045BEB0)) < 0x10U) {
        strcpy((char *) &(*(u8 *)D_004B8A20), (char *) &(*(u8 *)D_0045BEB0));
    }
    MemStackReset_14d830(&(*(u8 *)D_004B8A20));
    temp_17 = GetWorldDataMgr_1fedf0();
    temp_16 = GetGameData_1fede0();
    WorldDataMgrInit_3f3060(temp_17, &(*(u8 *)D_004B8A20));
    GameDataCreate_3ee1f0(temp_16, &(*(u8 *)D_004B8A20));
    return temp_2;
    return 0;
}
