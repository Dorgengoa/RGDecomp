#include "types.h"

extern void AabbCorners_13e190(void *, s32, s32);
extern void MtxTransformPointsMinMax_13c780(void *, s32, void *, s32, s32, s32);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void AabbTransformBounds_13c710(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    u128 v40[8];

    AabbCorners_13e190(v40, p3, p4);
    MtxTransformPointsMinMax_13c780(v40, p2, v40, 8, p0, p1);
}
