/* rgp:protos */
#define RGP_SELF_CharaSysStateField28ValidRelated_3a3920 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

u8 CharaSysStateField28ValidRelated_3a3920(s32 p0)
{
    s32 r;

    r = CharaSysStateGetField28Related_3a3820(p0);
    return (r >= 0);
}
