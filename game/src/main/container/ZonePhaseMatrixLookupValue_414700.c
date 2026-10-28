/* rgp:protos */
#define RGP_SELF_ZonePhaseMatrixLookupValue_414700 1
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
    u8 pad000[0x4];
    s32 m04;
};

s32 ZonePhaseMatrixLookupValue_414700(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    struct Obj0 *r0;
    s32 t0;

    r0 = ZonePhaseMatrixLookup_414730(p0, p1, p2, p3, p4, p5);
    if (r0 != 0) {
        t0 = r0->m04;
        return t0;
    }
    return 0;
}
