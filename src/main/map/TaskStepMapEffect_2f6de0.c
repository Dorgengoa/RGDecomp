#include "types.h"

extern void *GetCurrentScene_1f5be0(void);
extern void *GetMapMgr_201a90(void);
extern f32 GameSceneGetTimeStep_1ceba0(void *);
extern void MapMgrSlotsStepObjs_1e1540(void *, f32);
extern void GameSceneMapEffectStep_1cef40(void *);

void TaskStepMapEffect_2f6de0(void)
{
    void *a;
    void *b;

    a = GetCurrentScene_1f5be0();
    b = GetMapMgr_201a90();
    MapMgrSlotsStepObjs_1e1540(b, GameSceneGetTimeStep_1ceba0(a));
    GameSceneMapEffectStep_1cef40(a);
}
