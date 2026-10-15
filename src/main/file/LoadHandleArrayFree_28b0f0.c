#include "types.h"

extern void LoadHandleFree_28b230(s32);
extern void LoadHandleArrayReset_28b160(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void LoadHandleArrayFree_28b0f0(s32 p0, s32 p1)
{
    s32 l0;

    if (p0 != 0) {
        l0 = 0;
        while (l0 < p1) {
            LoadHandleFree_28b230((p0 + (((l0 << 3) - l0) << 3)));
            l0 = (l0 + 1);
        }
        LoadHandleArrayReset_28b160(p0, p1);
        return;
    }
}
