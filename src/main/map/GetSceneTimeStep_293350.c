#include "types.h"

extern void *GetCurrentScene_1f5be0(void);
extern f32 GameSceneGetTimeStep_1ceba0(void *);

f32 GetSceneTimeStep_293350(void)
{
    void *p;

    p = GetCurrentScene_1f5be0();
    if (p != 0) {
        return GameSceneGetTimeStep_1ceba0(p);
    }
    return 1.0f;
}
