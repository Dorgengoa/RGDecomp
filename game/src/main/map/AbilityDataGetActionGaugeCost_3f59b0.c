/* rgp:protos */
#define RGP_SELF_AbilityDataGetActionGaugeCost_3f59b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x44];
    u16 m44;
};

s32 AbilityDataGetActionGaugeCost_3f59b0(s32 p0)
{
    struct Obj0 *r0;
    u16 t0;

    r0 = AbilityDataGetKind0Rec_3f5db0(p0);
    if (r0 != 0) {
        t0 = r0->m44;
        return t0;
    }
    return 0;
}
