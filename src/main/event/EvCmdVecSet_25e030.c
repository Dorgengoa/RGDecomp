#include "types.h"

typedef struct { f32 x, y, z, w; } V_0025e030;
typedef struct { s32 a, b; } T_0025e030;

extern void ScriptArgsToVec4_26a220(V_0025e030 *, T_0025e030 *);
extern void ScriptSetRefFloat_26a1c0(T_0025e030 *, f32);

s32 EvCmdVecSet_25e030(T_0025e030 *q)
{
    V_0025e030 v;

    ScriptArgsToVec4_26a220(&v, &q[3]);
    ScriptSetRefFloat_26a1c0(q++, v.x);
    ScriptSetRefFloat_26a1c0(q++, v.y);
    ScriptSetRefFloat_26a1c0(q, v.z);
    return 1;
}
