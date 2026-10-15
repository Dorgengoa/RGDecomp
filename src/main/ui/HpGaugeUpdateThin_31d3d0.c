#include "types.h"

extern void HpGaugeTickSlots_31e6e0(s32);
extern void HpGaugeAnimValues_31e3b0(s32);
extern s32 HpGaugeFadeStep_31d200(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 HpGaugeUpdateThin_31d3d0(s32 p0)
{
    s32 r2;

    HpGaugeTickSlots_31e6e0(p0);
    HpGaugeAnimValues_31e3b0(p0);
    r2 = HpGaugeFadeStep_31d200(p0);
    return 1;
}
