/* rgp:protos */
#define RGP_SELF_NavGraphRelease_311170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void NavGraphRelease_311170(s32 p0)
{
    NavGraphStorageRelease_3114b0((p0 + 0x90));
    NavGraphReset_3111a0(p0);
}
