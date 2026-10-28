/* rgp:protos */
#define RGP_SELF_AiCmdGetBattleCenter_2c2cb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V_002c2cb0;
typedef struct { s32 a, b; } T_002c2cb0;

/*rgp*/
/*rgp*/

s32 AiCmdGetBattleCenter_2c2cb0(T_002c2cb0 *q)
{
    V_002c2cb0 v __attribute__((aligned(16)));

    GameFlowGetBattleCenter_283390(&v);
    ScriptSlotStoreFloatRef_2cc8e0(q++, v.x);
    ScriptSlotStoreFloatRef_2cc8e0(q++, v.y);
    ScriptSlotStoreFloatRef_2cc8e0(q, v.z);
    return 1;
}
