#include "types.h"

typedef struct { f32 x, y, z, w; } V_0025dae0;
typedef struct { u8 d[0x30]; } P_0025dae0;

extern void ScriptArgsToVec4_26a220(V_0025dae0 *, void *);
extern f32 VecDistance_13d3d0(V_0025dae0 *, V_0025dae0 *);
extern void ScriptSetRefFloat_26a1c0(void *, f32);

s32 EvCmdVecDistance_25dae0(P_0025dae0 *p)
{
    V_0025dae0 a;
    V_0025dae0 b;
    f32 r;

    ScriptArgsToVec4_26a220(&a, p);
    ScriptArgsToVec4_26a220(&b, (void *)((u8 *)p + 0x18));
    p = (P_0025dae0 *)((u8 *)p + 0x30);
    r = VecDistance_13d3d0(&a, &b);
    ScriptSetRefFloat_26a1c0(p, r);
    return 1;
}
