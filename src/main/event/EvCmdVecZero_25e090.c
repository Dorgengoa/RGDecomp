#include "types.h"

typedef struct { s32 a; s32 b; } T_0025e090;

extern void ScriptSetRefFloat_26a1c0(T_0025e090 *, f32);

s32 EvCmdVecZero_25e090(T_0025e090 *q)
{
    ScriptSetRefFloat_26a1c0(q++, 0.0f);
    ScriptSetRefFloat_26a1c0(q++, 0.0f);
    ScriptSetRefFloat_26a1c0(q, 0.0f);
    return 1;
}
