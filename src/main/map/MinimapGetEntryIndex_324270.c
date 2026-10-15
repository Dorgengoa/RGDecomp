#include "types.h"

extern s32 MinimapGetCurOrPendingEntry_32a920(s32);
extern s32 MinimapGetPendingOrCurEntry_32a8f0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x2C];
    s32 m2C;
};

s32 MinimapGetEntryIndex_324270(s32 p0, s32 p1)
{
    struct Obj0 *rv2;
    s32 r0;
    s32 r1;
    s32 t0;

    if (p1 != 0) {
        r0 = MinimapGetCurOrPendingEntry_32a920(p0);
        rv2 = (struct Obj0 *)r0;
    } else {
        r1 = MinimapGetPendingOrCurEntry_32a8f0(p0);
        rv2 = (struct Obj0 *)r1;
    }
    if (rv2 == 0) {
        return -1;
    }
    t0 = rv2->m2C;
    return t0;
}
