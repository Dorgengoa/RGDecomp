/* rgp:protos */
#define RGP_SELF_GameDataHeapInit_1fed00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
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
    temp_2_2 = ((s32)Memalign_130ba8(0x10, temp_2 * 0x10));
    if (temp_2_2 == 0) {
        return 0;
    }
    MemStackClear_14dff0(&(*(u8 *)D_004B8A20));
    MemStackInit_14d810(&(*(u8 *)D_004B8A20), temp_2_2, temp_2);
    if (strlen((char *) &(*(u8 *)D_0045BEB0)) < 0x10U) {
        strcpy((char *) &(*(u8 *)D_004B8A20), (char *) &(*(u8 *)D_0045BEB0));
    }
    MemStackReset_14d830(&(*(u8 *)D_004B8A20));
    temp_17 = ((s32)GetWorldDataMgr_1fedf0());
    temp_16 = ((s32)GetGameData_1fede0());
    WorldDataMgrInit_3f3060(temp_17, &(*(u8 *)D_004B8A20));
    GameDataCreate_3ee1f0(temp_16, &(*(u8 *)D_004B8A20));
    return temp_2;
    return 0;
}
