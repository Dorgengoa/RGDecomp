#include "types.h"

typedef union { f32 f; s32 i; } U_0025c2d0;
typedef struct { f32 x, y; } V2_0025c2d0;
typedef struct { s32 a, b; } T_0025c2d0;

extern void func_524CE0(V2_0025c2d0 *);
extern void ScriptSetRefInt_26a1e0(T_0025c2d0 *, s32);

s32 EvCmdMenuInsectEntryGetResult_25c2d0(T_0025c2d0 *q)
{
    U_0025c2d0 b[2];
    V2_0025c2d0 a;

    func_524CE0(&a);
    *(V2_0025c2d0 *)b = a;
    ScriptSetRefInt_26a1e0(q++, b[0].i);
    ScriptSetRefInt_26a1e0(q, b[1].i);
    return 1;
}
