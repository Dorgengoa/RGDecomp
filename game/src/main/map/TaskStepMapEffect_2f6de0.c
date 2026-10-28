/* rgp:protos */
#define RGP_SELF_TaskStepMapEffect_2f6de0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void TaskStepMapEffect_2f6de0(void)
{
    void *a;
    void *b;

    a = GetCurrentScene_1f5be0();
    b = GetMapMgr_201a90();
    MapMgrSlotsStepObjs_1e1540(b, GameSceneGetTimeStep_1ceba0(a));
    GameSceneMapEffectStep_1cef40(a);
}
