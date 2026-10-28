/* rgp:protos */
#define RGP_SELF_OptionsHeapInit_3d6310 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 OptionsHeapInit_3d6310(s32 p0, s32 p1)
{
    s32 rv1;
    s32 r0;

    rv1 = 1;
    if (p1 == 0) {
        rv1 = 0;
    } else {
        r0 = (OptionsInit_3d6340((int)p0), (s32)0);
        rv1 = 1;
    }
    return rv1;
}
