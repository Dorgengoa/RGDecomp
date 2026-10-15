#include "types.h"

extern f32 ScriptSlotGetFloat_2cc9a0(void *);
extern s32 Rand_133710(void);
extern void ScriptSlotStoreFloatRef_2cc8e0(void *, f32);

s32 AiCmdRandFloat_2cbf00(void *a0, s32 mode)
{
    void *q;
    f32 r1;
    f32 f;

    if (mode != 2) {
        return 0;
    }
    q = a0;
    a0 = (u8 *)a0 + 8;
    r1 = ScriptSlotGetFloat_2cc9a0(q);
    f = (f32)Rand_133710();
    ScriptSlotStoreFloatRef_2cc8e0(a0, (f32)(s32)(r1 * f / 2147483648.0f));
    return 1;
}
