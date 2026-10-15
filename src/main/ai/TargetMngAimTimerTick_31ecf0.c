#include "types.h"

typedef struct { s32 pad[60]; f32 fF0; } T_0031ecf0;

extern void *GetCurrentScene_1f5be0(void);
extern f32 GameSceneGetTimeStep_1ceba0(void *);

void TargetMngAimTimerTick_31ecf0(T_0031ecf0 *p)
{
    void *q;
    f32 t;

    q = GetCurrentScene_1f5be0();
    t = p->fF0 + GameSceneGetTimeStep_1ceba0(q);
    p->fF0 = t;
    if (t > 25.0f) {
        p->fF0 = 0.0f;
    }
}
