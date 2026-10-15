#include "types.h"

typedef struct E8_FUN_00334350 {
    s32 a;
    s32 b;
} E8_FUN_00334350;

extern f32 sqrtf(f32 x);
extern f32 ScriptSlotGetFloat_334890(E8_FUN_00334350 *p);
extern void ScriptSlotStoreFloatRef_3347d0(E8_FUN_00334350 *p, f32 v);

s32 ScriptCmdSqrt_334350(E8_FUN_00334350 *q, s32 mode)
{
    f32 v;

    if (mode != 2) return 0;
    v = ScriptSlotGetFloat_334890(q++);
    ScriptSlotStoreFloatRef_3347d0(q, sqrtf(v));
    return 1;
}
