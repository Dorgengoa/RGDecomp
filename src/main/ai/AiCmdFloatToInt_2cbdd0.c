#include "types.h"

typedef struct { s32 a; s32 b; } T_002cbdd0;

extern f32 ScriptSlotGetFloat_2cc9a0(T_002cbdd0 *);
extern void ScriptSlotStoreIntRef_2cc900(T_002cbdd0 *, s32);

s32 AiCmdFloatToInt_2cbdd0(T_002cbdd0 *q)
{
    f32 f;

    f = ScriptSlotGetFloat_2cc9a0(q++);
    ScriptSlotStoreIntRef_2cc900(q, (s32)f);
    return 1;
}
