#include "types.h"

typedef struct Obj_FUN_001fe4f0 Obj_FUN_001fe4f0;

extern Obj_FUN_001fe4f0 *GetGameData_1fede0(void);
extern void MapApplySaveStateMaybe_1fe560(void);
extern void MapObjParamRefreshCondsMaybe_3ed0a0(Obj_FUN_001fe4f0 *o, s32 n);
extern void BgmParamRefreshCondsMaybe_3ece90(Obj_FUN_001fe4f0 *o, s32 n);
extern void TranspParamRefreshCondsMaybe_3ecce0(Obj_FUN_001fe4f0 *o, s32 n);
extern void TreasureBoxParamRefreshCondsMaybe_3eca40(Obj_FUN_001fe4f0 *o, s32 n);
extern void NpcDataRefreshCondsMaybe_3eb930(Obj_FUN_001fe4f0 *o, s32 n);

void EventCondRefreshAllMaybe_1fe4f0(void)
{
    Obj_FUN_001fe4f0 *o;

    o = GetGameData_1fede0();
    MapApplySaveStateMaybe_1fe560();
    MapObjParamRefreshCondsMaybe_3ed0a0(o, -1);
    BgmParamRefreshCondsMaybe_3ece90(o, -1);
    TranspParamRefreshCondsMaybe_3ecce0(o, -1);
    TreasureBoxParamRefreshCondsMaybe_3eca40(o, -1);
    NpcDataRefreshCondsMaybe_3eb930(o, -1);
}
