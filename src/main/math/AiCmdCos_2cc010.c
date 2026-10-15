#include "types.h"

typedef struct S8 {
    s32 a;
    s32 b;
} S8;

extern f32 ScriptSlotGetFloat_2cc9a0(S8 *p);
extern f32 Cosf_128d30(f32 x);
extern void ScriptSlotStoreFloatRef_2cc8e0(S8 *p, f32 x);

s32 AiCmdCos_2cc010(S8 *a0, s32 mode)
{
    S8 *p;
    f32 v;

    p = a0;
    if (mode == 2) {
        goto body;
    }
    return 0;
body:
    v = ScriptSlotGetFloat_2cc9a0(p++);
    ScriptSlotStoreFloatRef_2cc8e0(p, Cosf_128d30(v));
    return 1;
}
