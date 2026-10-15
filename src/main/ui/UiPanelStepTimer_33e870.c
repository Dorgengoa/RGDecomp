#include "types.h"

/* Step a signed counter towards zero and return it.  The initial read is
   named (retail loads it once and compares it twice); the address of the
   slot is CSEd for the two stores and the final reload. */

struct S {
    u8 pad000[0x38];
    s32 m38[1];
};

s32 UiPanelStepTimer_33e870(struct S *p0, s32 p1)
{
    s32 v;

    v = p0->m38[p1];
    if (v > 0) {
        p0->m38[p1] = v - 1;
    } else if (v < 0) {
        p0->m38[p1] = v + 1;
    }
    return p0->m38[p1];
}
