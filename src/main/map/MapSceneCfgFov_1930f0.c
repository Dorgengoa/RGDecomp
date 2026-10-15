#include "types.h"

struct T1930F0 { f32 f0; };

extern struct T1930F0 *D_00481304;

s32 MapSceneCfgFov_1930f0(void)
{
    struct T1930F0 *p;

    p = D_00481304;
    if (p == 0) {
        return 0;
    }
    p->f0 = 52.0f;
    return 1;
}
