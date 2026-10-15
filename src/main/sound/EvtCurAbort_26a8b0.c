#include "types.h"

extern s32 EventPlayerAbort_2498b0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482040;

s32 EvtCurAbort_26a8b0(s32 p0)
{
    s32 t0;
    s32 rv1;
    s32 r0;

    t0 = D_00482040;
    rv1 = 1;
    if (t0 == 0) {
        rv1 = 0;
    } else {
        r0 = EventPlayerAbort_2498b0(t0, p0);
        rv1 = 1;
    }
    return rv1;
}
