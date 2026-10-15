#include "types.h"

extern s32 NavEdgeGetId_311720(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x114];
    s32 m114;
};

s32 NavGraphSetGoalEdge_3115f0(struct Obj0 *p0, s32 p1)
{
    s32 r0;

    if (p1 == 0) {
        p0->m114 = -1;
        return;
    }
    r0 = NavEdgeGetId_311720(p1);
    p0->m114 = r0;
    return r0;
}
