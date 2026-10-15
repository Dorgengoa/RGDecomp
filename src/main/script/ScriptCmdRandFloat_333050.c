#include "types.h"

extern f32 ScriptSlotGetFloat_334890(void *);
extern s32 Rand_133710(void);
extern void ScriptSlotStoreFloatRef_3347d0(void *, f32);

s32 ScriptCmdRandFloat_333050(void *a0, s32 mode)
{
    void *q;
    f32 r1;
    f32 f;

    if (mode != 2) {
        return 0;
    }
    q = a0;
    a0 = (u8 *)a0 + 8;
    r1 = ScriptSlotGetFloat_334890(q);
    f = (f32)Rand_133710();
    ScriptSlotStoreFloatRef_3347d0(a0, (f32)(s32)(r1 * f / 2147483648.0f));
    return 1;
}
