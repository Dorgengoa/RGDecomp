/* rgp:protos */
#define RGP_SELF_EventPathRecCtor_2e43f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EventPathRecCtor_2e43f0(s32 p0)
{
    s32 r1;

    EventRecCtor_2e5860(p0);
    r1 = (EventPathRecReset_2e43b0(p0), (s32)0);
    return p0;
}
