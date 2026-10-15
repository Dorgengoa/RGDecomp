#include "types.h"

extern s32 TargetRefAreaHasFlag80_2e6d70(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    s32 m08;
};

s32 EventRefListAnyAreaHasFlag80_304820(struct Obj0 *p0)
{
    s32 l0;
    s32 t0;
    s32 r1;

    l0 = 0;
    while (l0 < p0->m08) {
        t0 = p0->m04;
        r1 = TargetRefAreaHasFlag80_2e6d70((t0 + (l0 * 0x30)));
        if (r1 != 0) {
            return 1;
        }
        l0 = (l0 + 1);
    }
    return 0;
}
