#include "types.h"

extern void VecSub_1cbd00(void *, s32, s32);
extern f32 VecDistSq_1cb3c0(void *, void *);
extern f32 VecDotDiff_1cba40(void *, void *, void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

f32 SegmentProjectT_1ca340(s32 p0, s32 p1, s32 p2)
{
    u128 v50;
    u128 v40;
    f32 r2;
    f32 r3;

    VecSub_1cbd00(&v50, p1, p0);
    VecSub_1cbd00(&v40, p2, p0);
    r2 = VecDistSq_1cb3c0(&v50, &v40);
    if (0.0f == r2) {
        return 0.0f;
    }
    r3 = VecDotDiff_1cba40(&v50, &v40, &v50);
    return (r3 / r2);
}
