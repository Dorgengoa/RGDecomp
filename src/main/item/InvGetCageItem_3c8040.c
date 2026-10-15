#include "types.h"

extern void *InvFindByRecKey_3c8140(void *a, s32 b, s32 c, void *d, s32 e);
extern s32 InvObjCastToCage_3d3c80(void *p);

s32 InvGetCageItem_3c8040(void *a0, void *a1)
{
    void *r;

    r = InvFindByRecKey_3c8140(a0, 0xC, 0x4B1, a1, 0);
    if (r == 0) {
        r = InvFindByRecKey_3c8140(a0, 0xC, 0x4B1, a1, 9);
        if (r == 0) {
            return 0;
        }
    }
    return InvObjCastToCage_3d3c80(r);
}
