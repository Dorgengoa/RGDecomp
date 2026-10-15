/* s41 agent10: MATCH (early-return order). */
#include "types.h"

extern void MemStackReturnToOwnerMaybe_14dad0(s32);
extern s32 MemStackHeapAlloc_14db10(s32, s32, s32, s32);
extern void MemStackHeapFree_14dcb0(s32, s32);
extern void NameTableFreeGroup_158ac0(s32, s32);
extern void NameTableRegisterImArchive_1594d0(s32, s32, s32, s32, s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void LoaderReleaseById_1cd340(s32, s32);
extern s32 LoaderGetData_1cd490(s32, s32, s32 *);
extern s32 LoaderGetStatus_1cd4f0(s32, s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern s32 GetReadBuffHeap_2025e0(void);
extern void MemMoveIfDiff_289c60(s32, s32, s32, s32);
extern void WorkIconBuildPartyWeaponsMaybe_28dde0(void);
extern s32 D_0047E5B8;
extern u8 D_0047E5BC;

s32 MenuIconAllTexLoadPoll_2056b0(void)
{
    s32 sp6C;
    s32 temp_16;
    s32 temp_2;
    s32 temp_19;
    s32 temp_18;
    s32 temp_2_2;

    temp_16 = GetLoaderMgr_1f59d0();
    if (D_0047E5BC != 0) {
        return 0;
    }
    if (D_0047E5B8 == -1) {
        return 0;
    }
    D_0047E5BC = LoaderGetStatus_1cd4f0(temp_16, D_0047E5B8) != 0;
    if (D_0047E5BC == 1) {
        temp_2 = GetReadBuffHeap_2025e0();
        temp_19 = MemStackHeapAlloc_14db10(temp_2, 2, 0, 0x40);
        temp_18 = GetDrawCtxNameTable_15de40();
        temp_2_2 = LoaderGetData_1cd490(temp_16, D_0047E5B8, &sp6C);
        MemMoveIfDiff_289c60(temp_2_2, sp6C, temp_2_2, 0xF081);
        NameTableRegisterImArchive_1594d0(temp_18, temp_2_2, 0x30B, temp_2, 0);
        WorkIconBuildPartyWeaponsMaybe_28dde0();
        NameTableFreeGroup_158ac0(temp_18, 0x30B);
        LoaderReleaseById_1cd340(temp_16, D_0047E5B8);
        MemStackReturnToOwnerMaybe_14dad0(temp_2);
        MemStackHeapFree_14dcb0(temp_2, temp_19);
        D_0047E5B8 = -1;
        return 1;
    }
    return 0;
}
