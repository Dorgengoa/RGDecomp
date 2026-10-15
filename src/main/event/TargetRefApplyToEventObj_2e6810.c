#include "types.h"

extern s32 TargetRefGetMatrix_2e6870(s32, void *);
extern s32 EventObjSetFromMatrix_2e72f0(s32, void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 TargetRefApplyToEventObj_2e6810(s32 p0, s32 p1)
{
    u128 v20[4];
    s32 rv3;
    s32 r0;
    s32 rv2;
    s32 r1;

    if (p1 == 0) {
        rv3 = 0;
    } else {
        r0 = TargetRefGetMatrix_2e6870(p0, v20);
        rv2 = 1;
        if (r0 == 0) {
            rv2 = 0;
        } else {
            r1 = EventObjSetFromMatrix_2e72f0(p1, v20);
            rv2 = 1;
        }
        rv3 = rv2;
    }
    return rv3;
}
