#include "types.h"

extern void MapApplyAreaEnv_1e2bc0(s32, s32, s32);
extern s32 MapSlotsFindById_1e4b90(s32, s32, s32);
extern s32 MapGetEnvSlots_1e57a0(s32);
extern s32 MapEnvSlotGetId_1e5b50(s32, s32);
extern s32 GetActionMgr_1fdb50(void);
extern void *GetGameData_1fede0(void);
extern s32 GetMapMgr_201a90(void);
extern s32 CharaGetAreaId_213c90(s32);
extern s32 ActionMgrFindById_233b50(s32, s16);

void TaskUpdateFogParam_201240(void)
{
    void *temp_16;
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_16_2;
    s32 temp_16_3;

    temp_16 = GetGameData_1fede0();
    temp_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(),
                           *(s16 *)((u8 *)*(void **)((u8 *)temp_16 + 0x18) + 0x18E));
    if (temp_2 != 0) {
        temp_2_2 = GetMapMgr_201a90();
        temp_16_2 = MapGetEnvSlots_1e57a0(temp_2_2);
        temp_16_3 = CharaGetAreaId_213c90(temp_2);
        MapApplyAreaEnv_1e2bc0(temp_2_2, temp_16_3, !MapSlotsFindById_1e4b90(temp_2_2, MapEnvSlotGetId_1e5b50(temp_16_2, 1), 0));
    }
}
