/* rgp:protos */
#define RGP_SELF_MapBlockAnimStepIfActive_1dec90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapBlockAnimStepIfActive_1dec90(s32 p0, f32 fa0)
{
    s32 r0;
    s32 rv2;
    s32 r1;

    r0 = ((unsigned char)MapDataIsLoadedOrUnloading_1e7980(p0));
    rv2 = r0;
    if (r0 != 0) {
        r1 = (MapDataAnimStep_1e6600(p0, fa0), (s32)0);
        rv2 = r1;
    }
    return rv2;
}
