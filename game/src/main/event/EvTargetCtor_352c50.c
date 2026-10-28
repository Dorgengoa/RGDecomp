/* rgp:protos */
#define RGP_SELF_EvTargetCtor_352c50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvTargetCtor_352c50(s32 p0)
{
    s32 r3;

    TargetRefCtor_2e71f0(p0);
    XformCtor_2e79c0((p0 + 0x38));
    XformCtor_2e79c0((p0 + 0x80));
    r3 = (EvTargetInit_352be0(p0), (s32)0);
    return p0;
}
