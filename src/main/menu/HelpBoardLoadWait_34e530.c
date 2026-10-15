#include "types.h"

extern void MemStackAlign64_14d8e0(s32 arg0);
extern s32 MemStackPeekQw_14d9d0(s32 arg0, s32 arg1);
extern void MemStackAllocAligned64_14da10(s32 arg0, s32 arg1);
extern void NameTableFreeGroup_158ac0(s32 arg0, s32 arg1);
extern void NameTableRegisterImArchive_1594d0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void LoaderReleaseById_1cd340(s32 arg0, s32 arg1);
extern s32 LoaderGetData_1cd490(s32 arg0, s32 arg1, s32 *arg2);
extern s32 GetLoaderMgr_1f59d0(void);
extern void UiEntryListSelectByTag_28ea90(s32 arg0, s32 arg1, s32 arg2);
extern void StateMachineSetState_28ede0(s32 arg0, s32 arg1, s32 arg2);
extern void UiFadeWidgetAlpha_290690(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
extern void UiMoveWidgetUniform_290f50(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5);
extern s32 HelpBoardIsFileLoaded_34dc60(void);
extern void memcpy(s32 dst, s32 src, s32 n);
extern f32 D_0047D4B0;
extern s32 D_0047F6E4;
extern s32 D_00482338;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;

s32 HelpBoardLoadWait_34e530(s32 arg0, s32 arg1)
{
    s32 temp_19;
    s32 temp_2;
    s32 temp_17;
    s32 sp5C;
    s32 temp_16;
    s32 var_2;

    if (arg1 != 0) {
        UiMoveWidgetUniform_290f50(D_00482360, 0x20F, 0x200, 0x4B, 0, D_0047D4B0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x20F, 0.0f, -0.0625f, -1.0f);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
    }
    if (HelpBoardIsFileLoaded_34dc60() != 0) {
        temp_19 = GetDrawCtxNameTable_15de40();
        temp_2 = GetLoaderMgr_1f59d0();
        if (temp_2 == 0) {
            return 0;
        }
        {
            temp_17 = LoaderGetData_1cd490(temp_2, D_0047F6E4, &sp5C);
            NameTableFreeGroup_158ac0(temp_19, 0x32E);
            MemStackAlign64_14d8e0(D_00482338);
            temp_16 = MemStackPeekQw_14d9d0(D_00482338, 1);
            MemStackAllocAligned64_14da10(D_00482338, sp5C / 16 + 1);
            memcpy(temp_16, temp_17, sp5C);
            NameTableRegisterImArchive_1594d0(temp_19, temp_16, 0x32E, D_00482338, 0);
            LoaderReleaseById_1cd340(temp_2, D_0047F6E4);
            StateMachineSetState_28ede0(D_0048235C, 0x87, 0);
        }
    }
    return 1;
}
