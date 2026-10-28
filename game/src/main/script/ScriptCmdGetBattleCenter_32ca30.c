/* rgp:protos */
#define RGP_SELF_ScriptCmdGetBattleCenter_32ca30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V_0032ca30;

/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdGetBattleCenter_32ca30(void *p, s32 n)
{
    V_0032ca30 v __attribute__((aligned(16)));

    if (n < 4) return 1;
    GameFlowGetBattleCenter_283390(&v);
    ScriptSlotStoreFloatRef_3347d0(p, v.x);
    ScriptSlotStoreFloatRef_3347d0((void *)((s32)p + 8), v.y);
    ScriptSlotStoreFloatRef_3347d0((void *)((s32)p + 0x10), v.z);
    ScriptSlotStoreFloatRef_3347d0((void *)((s32)p + 0x18), GameFlowGetBattleRadius_283380());
    return 1;
}
