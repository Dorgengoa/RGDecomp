/* rgp:protos */
#define RGP_SELF_UnitClampVitalsThunk_3bc6a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 UnitClampVitalsThunk_3bc6a0(s32 p0)
{
    s32 r0;

    r0 = ((unsigned char)UnitClampVitalsThunk_3be030(p0));
    return (r0 & 0xFF);
}
