#include "types.h"

extern void MemStackAlign64_14d8e0(void *);
extern s32 MemStackPeekQw_14d9d0(void *, s32);
extern void MemStackAllocAligned64_14da10(void *, s32);
extern void NameTableRegisterImArchive_1594d0(s32, s32, s32, void *, s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void LoaderReleaseById_1cd340(s32, s32);
extern s32 LoaderGetData_1cd490(s32, s32, s32 *);
extern s32 LoaderGetStatus_1cd4f0(s32, s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern void memcpy(s32, s32, s32);
extern s32 D_0047E5C0;
extern u8 D_0047E5C4;
extern u8 D_004BBCE0[0x400];

s32 MenuBattleIconLoadPoll_204b60(void) {
    s32 temp_19;
    s32 temp_18;
    s32 temp_17;
    s32 temp_16;
    s32 sp5C;

    temp_19 = GetLoaderMgr_1f59d0();
    if (D_0047E5C4 != 0) {
        return 0;
    }
    if (D_0047E5C0 <= -1) {
        return 0;
    }
    D_0047E5C4 = LoaderGetStatus_1cd4f0(temp_19, D_0047E5C0) != 0;
    if (D_0047E5C4 == 1) {
    temp_18 = GetDrawCtxNameTable_15de40();
    MemStackAlign64_14d8e0(D_004BBCE0);
    temp_16 = MemStackPeekQw_14d9d0(D_004BBCE0, 1);
    temp_17 = LoaderGetData_1cd490(temp_19, D_0047E5C0, &sp5C);
    MemStackAllocAligned64_14da10(D_004BBCE0, sp5C / 16 + 1);
    memcpy(temp_16, temp_17, sp5C);
    NameTableRegisterImArchive_1594d0(temp_18, temp_16, 0x32C, D_004BBCE0, 0);
    LoaderReleaseById_1cd340(temp_19, D_0047E5C0);
    D_0047E5C0 = -1;
    return 1;
    }
    return 0;
}
