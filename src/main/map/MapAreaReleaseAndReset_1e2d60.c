#include "types.h"

extern s32 MapAreaRelease_1d9ee0(s32, s32);
extern s32 MapAreaInit_1dcf90(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapAreaReleaseAndReset_1e2d60(s32 p0, s32 p1, s32 p2)
{
    s32 rv3;
    s32 r0;
    s32 rv2;
    s32 r1;

    rv3 = rv2;
    if (p1 == 0) {
        rv3 = 0;
    } else {
        r0 = MapAreaRelease_1d9ee0(p1, p2);
        rv2 = 1;
        if (r0 == 0) {
            rv2 = 0;
        } else {
            r1 = MapAreaInit_1dcf90(p1);
            rv2 = 1;
        }
        rv3 = rv2;
    }
    return rv3;
}
