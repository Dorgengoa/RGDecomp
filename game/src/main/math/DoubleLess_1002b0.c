/* rgp:protos */
#define RGP_SELF_DoubleLess_1002b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

u8 DoubleLess_1002b0(double p0, double p1)
{
    s32 r;

    r = DoubleCmp_13b948(p0, p1);
    return (r < 0);
}
