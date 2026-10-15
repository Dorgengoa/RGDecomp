#include "types.h"

extern void MemStackReturnToOwnerMaybe_14dad0(s32 v);
extern s32 MemStackHeapAlloc_14db10(s32 a, s32 b, s32 c, s32 d);
extern void MemStackHeapFree_14dcb0(s32 a, s32 b);

s32 HeapProbeLargestGapMaybe_2504d0(u8 *arg0)
{
    s32 r;
    s32 v;

    v = *(s32 *)(arg0 + 0x1808);
    r = MemStackHeapAlloc_14db10(v, 2, 0, 0x40);
    MemStackReturnToOwnerMaybe_14dad0(v);
    MemStackHeapFree_14dcb0(v, r);
    return r;
}
