#include "types.h"

extern void StringReplace_106f90(void *a, s32 b, s32 c, s32 d, s32 e, s8 f);

void StringReplaceRange_1b3da0(void *a, s32 b, s32 c, s32 d, s32 e, s32 f)
{
    volatile s8 g[1];

    g[0] = f;
    StringReplace_106f90(a, b, c, d, e, (s8)f);
}
