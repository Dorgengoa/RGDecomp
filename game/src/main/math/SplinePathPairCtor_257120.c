/* rgp:protos */
#define RGP_SELF_SplinePathPairCtor_257120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 SplinePathPairCtor_257120(s32 p0)
{
    s32 r2;

    SplineCtor_2578c0((p0 + 0x208));
    SplineCtor_2578c0((p0 + 0x5A4));
    r2 = (SplinePathPairReset_257030(p0), (s32)0);
    return p0;
}
