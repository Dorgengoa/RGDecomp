/* rgp:protos */
#define RGP_SELF_EventParamRecCtor_2e3cf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EventParamRecCtor_2e3cf0(s32 p0)
{
    s32 r1;

    EventRecCtor_2e5860(p0);
    r1 = (EventParamRecReset_2e3c50(p0), (s32)0);
    return p0;
}
