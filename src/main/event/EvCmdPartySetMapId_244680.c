#include "types.h"

extern void MapApplyAreaEnv_1e2bc0(s32, s16, s32);
extern s32 MapSlotsFindBlockByName_1e4910(s32, s32, s32);
extern s32 MapSlotsFindBlockById_1e49b0(s32, s32, s32);
extern s32 MapDataGetId_1e7bd0(s32);
extern void *GetGameData_1fede0(void);
extern s32 GetMapMgr_201a90(void);
extern s32 ScriptGetCodeAddr_249050(s32 *);
extern s32 ScriptGetInt_2490f0(s32 *);
extern void PartySetMapId_3c9cc0(void *, s32);

s32 EvCmdPartySetMapId_244680(s32 *arg0, s32 arg1)
{
    s32 temp_17;
    s32 var_2;
    u8 *temp_16;

    if (arg1 != 1) {
        return 0;
    }
    temp_17 = GetMapMgr_201a90();
    if (*arg0 == 2) {
        var_2 = MapSlotsFindBlockByName_1e4910(temp_17, ScriptGetCodeAddr_249050(arg0), 0);
    } else {
        var_2 = MapSlotsFindBlockById_1e49b0(temp_17, ScriptGetInt_2490f0(arg0), 0);
    }
    if (var_2 == 0) {
        return 0;
    }
    temp_16 = (u8 *)GetGameData_1fede0();
    PartySetMapId_3c9cc0(*(void **)(temp_16 + 0x18), MapDataGetId_1e7bd0(var_2));
    MapApplyAreaEnv_1e2bc0(temp_17, *(s16 *)(*(u8 **)(temp_16 + 0x18) + 0x30), 1);
    return 1;
}
