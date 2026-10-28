/* rgp:protos */
#define RGP_SELF_EventCondRefreshAllMaybe_1fe4f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_001fe4f0 Obj_FUN_001fe4f0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void EventCondRefreshAllMaybe_1fe4f0(void)
{
    Obj_FUN_001fe4f0 *o;

    o = ((Obj_FUN_001fe4f0 *)GetGameData_1fede0());
    MapApplySaveStateMaybe_1fe560();
    MapObjParamRefreshCondsMaybe_3ed0a0(o, -1);
    BgmParamRefreshCondsMaybe_3ece90(o, -1);
    TranspParamRefreshCondsMaybe_3ecce0(o, -1);
    TreasureBoxParamRefreshCondsMaybe_3eca40(o, -1);
    NpcDataRefreshCondsMaybe_3eb930(o, -1);
}
