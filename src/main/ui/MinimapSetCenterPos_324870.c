#include "types.h"

typedef struct {
    u8  pad000[0x30];
    f32 f30, f34, f38;
    u8  pad03C[4];
    s32 f40, f44, f48;
} T_00324870;

extern void MinimapScrollToClamped_324530(T_00324870 *, f32 *, s32, s32);

s32 MinimapSetCenterPos_324870(T_00324870 *p, f32 *q)
{
    p->f40 = 0;
    p->f44 = 0;
    p->f48 = 0;
    {
        f32 v[4] = {0};

        v[0] = q[0];
        v[1] = q[1];
        v[2] = q[2];
        p->f30 = v[0];
        p->f34 = v[1];
        p->f38 = v[2];
        MinimapScrollToClamped_324530(p, v, 0, 0);
    }
    return 1;
}
