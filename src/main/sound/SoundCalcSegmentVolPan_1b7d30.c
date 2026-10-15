#include "types.h"

extern s32 DisableIntr_120660(void);
extern void PointSegmentClosest_13dcc0(void *, s32, s32, void *);
extern void SoundCalcDistVolPan_1b7de0(s32, s32, void *, f32, f32);
extern void EnableIntr_1206b0(void);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481480;

void SoundCalcSegmentVolPan_1b7d30(s32 p0, s32 p1, s32 p2, s32 p3, f32 fa0, f32 fa1)
{
    u128 v70;
    s32 r0;

    r0 = DisableIntr_120660();
    PointSegmentClosest_13dcc0(&D_00481480, p2, p3, &v70);
    SoundCalcDistVolPan_1b7de0(p0, p1, &v70, fa0, fa1);
    if (r0 != 0) {
        EnableIntr_1206b0();
    }
}
