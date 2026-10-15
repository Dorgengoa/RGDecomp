#include "types.h"
typedef struct { f32 x, y, z; } V_0025f9c0;
typedef union { f32 f; s32 i; } U_0025f9c0;
extern void func_5219C0(V_0025f9c0 *);
extern void ScriptSetRefInt_26a1e0(void *, s32);

s32 EvCmdMenuThinkGetResult_25f9c0(void *p)
{
    U_0025f9c0 b[3];
    V_0025f9c0 a;

    func_5219C0(&a);
    *(V_0025f9c0 *)b = a;
    ScriptSetRefInt_26a1e0(p, b[1].i);
    return 1;
}
