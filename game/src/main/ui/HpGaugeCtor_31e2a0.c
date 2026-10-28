/* rgp:protos */
#define RGP_SELF_HpGaugeCtor_31e2a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 HpGaugeCtor_31e2a0(s32 p0)
{
    s32 r1;

    HpGaugeBaseCtor_31eab0(p0);
    r1 = (HpGaugeReset_31e1e0(p0), (s32)0);
    return p0;
}
