#include "types.h"

extern void HpGaugeBaseCtor_31eab0(s32);
extern s32 HpGaugeReset_31e1e0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 HpGaugeCtor_31e2a0(s32 p0)
{
    s32 r1;

    HpGaugeBaseCtor_31eab0(p0);
    r1 = HpGaugeReset_31e1e0(p0);
    return p0;
}
