#include "types.h"

/* The store to the gp scalar sits in the jal's delay slot, so it PRECEDES the
   call in source order.  The `addiu $4,$16,0x10 / beqz $4` pair is an inlined
   `if (q) release(q)` on a sub-object pointer. */

extern s32 D_00482A4C;

extern void *GetTargetMng_313dd0(void);
extern void TargetMngUnlock_31f4b0(void *p);
extern void TargetSlotHide_320960(void *p);

void TargetMngClearTarget_313c00(void)
{
    void *p;
    void *q;

    D_00482A4C = -1;
    p = GetTargetMng_313dd0();
    if (p != 0) {
        TargetMngUnlock_31f4b0(p);
        q = (u8 *)p + 0x10;
        if (q != 0) {
            TargetSlotHide_320960(q);
        }
    }
}
