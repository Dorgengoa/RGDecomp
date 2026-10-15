#include "types.h"
#pragma opt_propagation off

extern void MapBlockIdListAdd_1e3320(s32 arg0, s32 arg1);
extern s32 MapSlotsFindBlockByName_1e4910(s32 arg0, s32 arg1, s32 arg2);
extern void MapDataSetEnabled_1e7440(s32 arg0, s32 arg1);
extern s32 MapDataGetId_1e7bd0(s32 arg0);
extern s32 GetMapMgr_201a90(void);
extern s32 ScriptGetCodeAddr_249050(s32 arg0);
extern void EventAreaListAdd_24a220(s32 arg0, s32 arg1);
extern void *gEventContext;

s32 EvCmdMapBlockActivate_247fb0(s32 a)
{
    s32 arg0;
    s32 temp_18;
    s32 temp_16;
    u32 temp_2;

    arg0 = a;
    temp_18 = GetMapMgr_201a90();
    temp_2 = MapSlotsFindBlockByName_1e4910(temp_18, ScriptGetCodeAddr_249050(arg0), 0);
    temp_16 = temp_2;
    if (temp_2 == 0) {
        return 0;
    }
    arg0 = MapDataGetId_1e7bd0(temp_16);
    MapDataSetEnabled_1e7440(temp_16, 1);
    MapBlockIdListAdd_1e3320(temp_18, arg0);
    EventAreaListAdd_24a220(*(s32 *)((u8 *)gEventContext + 0x4) + 0x60, arg0);
    return 1;
}
