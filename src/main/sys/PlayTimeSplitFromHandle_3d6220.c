#include "types.h"

extern void *DoubleToU64_13ab28(s64);
extern s32 PlayTimeSplit_3d6350(void *, s32, s32, s32, s32);

/* Five arguments in, four passed straight through; the first is dereferenced
   as a 64-bit handle (`ld`) and mapped through DoubleToU64_13ab28. */

s32 PlayTimeSplitFromHandle_3d6220(s64 *h, s32 a, s32 b, s32 c, s32 d)
{
    return PlayTimeSplit_3d6350(DoubleToU64_13ab28(h[1]), a, b, c, d);
}
