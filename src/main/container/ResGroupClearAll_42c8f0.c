#include "types.h"

extern s32 ResGroupGetStack_42c720(s32, s32);
extern s32 MemStackClear_14dff0(s32);
extern s32 ResGroupReset_42c760(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 ResGroupClearAll_42c8f0(s32 p0)
{
    s32 l0;
    s32 l1;
    s32 r2;
    s32 r3;
    s32 r4;

    l1 = 0;
    do {
        r2 = ResGroupGetStack_42c720(p0, l1);
        r3 = MemStackClear_14dff0(r2);
        l0 = ((l1 + 1) < 4);
        l1 = (l1 + 1);
    } while (l0 != 0);
    r4 = ResGroupReset_42c760(p0);
    return r4;
}
