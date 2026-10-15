#include "types.h"

extern void Vec3ToVec4W1_311970(s32, void *);
extern void VecDistSq_1cb3c0(s32, void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void NavNodeDistSq_3118d0(s32 p0, s32 p1)
{
    u128 v20;

    Vec3ToVec4W1_311970(p0, &v20);
    VecDistSq_1cb3c0(p1, &v20);
}
