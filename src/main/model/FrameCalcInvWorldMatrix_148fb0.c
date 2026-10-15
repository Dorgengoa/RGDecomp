#include "types.h"

extern void FrameCalcWorldMatrix_148ff0(s32, void *);
extern void MtxInverse_13cf40(s32, void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void FrameCalcInvWorldMatrix_148fb0(s32 p0, s32 p1)
{
    u128 v20[4];

    FrameCalcWorldMatrix_148ff0(p0, v20);
    MtxInverse_13cf40(p1, v20);
}
