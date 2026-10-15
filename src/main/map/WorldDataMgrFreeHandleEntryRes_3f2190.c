#include "types.h"

extern void HandleEntryFreeRes_3f2210(void *, void *);
/* %hi/%lo, not %gp_rel -- the incomplete-array declaration is what forces the
   pair.  Element stride is 0x28 ((i*4+i)*8). */
extern s32 D_004644A0[];

s32 WorldDataMgrFreeHandleEntryRes_3f2190(u8 *p)
{
    s32 i;
    s32 n;

    if (*(s32 *)(p + 0x18) == 0) {
        return 0;
    }
    n = D_004644A0[0];
    for (i = 0; i < n; i++) {
        HandleEntryFreeRes_3f2210(p, *(u8 **)(p + 0x18) + i * 0x28);
    }
    return 1;
}
