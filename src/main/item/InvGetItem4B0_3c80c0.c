#include "types.h"

extern void *InvFindByRecKey_3c8140(void *a, s32 b, s32 c, void *d, s32 e);
extern s32 InvObjCastToItem4B0_3d3cd0(void *p);

s32 InvGetItem4B0_3c80c0(void *a0, void *a1)
{
    void *r;

    r = InvFindByRecKey_3c8140(a0, 0xC, 0x4B0, a1, 0);
    if (r == 0) {
        r = InvFindByRecKey_3c8140(a0, 0xC, 0x4B0, a1, 9);
        if (r == 0) {
            return 0;
        }
    }
    return InvObjCastToItem4B0_3d3cd0(r);
}
