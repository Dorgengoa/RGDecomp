#include "types.h"

typedef struct T { u8 b[0x10]; } T;

extern void ScriptSlotsToVec4_2cc920(T *d, void *s);
extern void ScriptSlotStoreVec3_2cc8a0(void *a, T *s);

s32 AiCmdVecCopy_2cc850(u8 *a, s32 k)
{
    T tmp;

    if (k != 6) return 0;
    ScriptSlotsToVec4_2cc920(&tmp, a + 0x18);
    ScriptSlotStoreVec3_2cc8a0(a, &tmp);
    return 1;
}
