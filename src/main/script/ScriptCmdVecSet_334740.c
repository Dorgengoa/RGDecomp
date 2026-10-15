#include "types.h"

typedef struct T { u8 b[0x10]; } T;

extern void ScriptSlotsToVec4_334810(T *d, void *s);
extern void ScriptSlotStoreVec3_334790(void *a, T *s);

s32 ScriptCmdVecSet_334740(u8 *a, s32 k)
{
    T tmp;

    if (k != 6) return 0;
    ScriptSlotsToVec4_334810(&tmp, a + 0x18);
    ScriptSlotStoreVec3_334790(a, &tmp);
    return 1;
}
