/* rgp:protos */
#define RGP_SELF_RandFloat_13c010 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

f32 RandFloat_13c010(void)
{
    s32 r0;

    r0 = Rand_133710();
    return (((f32)r0) / 2147483648.0f);
}
