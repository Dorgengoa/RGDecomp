#include "types.h"

extern void HpGaugeReset_31e1e0(s32);
extern void HpGaugeSetMode_31e2d0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void HpGaugeDisable_31d410(s32 p0)
{
    HpGaugeReset_31e1e0(p0);
    HpGaugeSetMode_31e2d0(p0, 2);
}
