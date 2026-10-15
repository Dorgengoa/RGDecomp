#include "types.h"

typedef struct { s32 a; s32 b; } T_002cbe10;

extern s32 ScriptSlotGetInt_2cc9c0(T_002cbe10 *);
extern void ScriptSlotStoreFloatRef_2cc8e0(T_002cbe10 *, f32);

s32 AiCmdIntToFloat_2cbe10(T_002cbe10 *q)
{
    s32 n;

    n = ScriptSlotGetInt_2cc9c0(q++);
    ScriptSlotStoreFloatRef_2cc8e0(q, (f32)n);
    return 1;
}
