#include "types.h"

extern s32 ScriptSlotGetInt_2cc9c0(void *);
extern s32 Rand_133710(void);
extern void ScriptSlotStoreIntRef_2cc900(void *, s32);

s32 AiCmdRandInt_2cbf80(void *a0, s32 mode)
{
    void *q;
    s32 r1;
    f32 f;

    if (mode != 2) {
        return 0;
    }
    q = a0;
    a0 = (u8 *)a0 + 8;
    r1 = ScriptSlotGetInt_2cc9c0(q);
    f = (f32)Rand_133710();
    ScriptSlotStoreIntRef_2cc900(a0, (s32)((f32)r1 * f / 2147483648.0f));
    return 1;
}
