/* rgp:protos */
#define RGP_SELF_EventParamRecCtorInit_2e3c80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EventParamRecCtorInit_2e3c80(s32 p0, s32 p1, f32 fa0, f32 fa1, f32 fa2)
{
    s32 r1;

    EventRecCtor_2e5860(p0);
    r1 = (EventParamRecInit_2e3bf0(p0, p1, fa0, fa1, fa2), (s32)0);
    return p0;
}
