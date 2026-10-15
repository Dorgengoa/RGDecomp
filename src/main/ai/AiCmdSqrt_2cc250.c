#include "types.h"

typedef struct E8_FUN_002cc250 {
    s32 a;
    s32 b;
} E8_FUN_002cc250;

extern f32 sqrtf(f32 x);
extern f32 ScriptSlotGetFloat_2cc9a0(E8_FUN_002cc250 *p);
extern void ScriptSlotStoreFloatRef_2cc8e0(E8_FUN_002cc250 *p, f32 v);

s32 AiCmdSqrt_2cc250(E8_FUN_002cc250 *q, s32 mode)
{
    f32 v;

    if (mode != 2) return 0;
    v = ScriptSlotGetFloat_2cc9a0(q++);
    ScriptSlotStoreFloatRef_2cc8e0(q, sqrtf(v));
    return 1;
}
