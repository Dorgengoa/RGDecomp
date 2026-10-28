/* rgp:protos */
#define RGP_SELF_Bit64Assign_33de80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* 64-bit bit set/clear.  Retail falls through into the SET path, so that is
   the source's if body.  The clear path needs dsll32/dsra32 0 because ~(1<<n)
   is computed in 64-bit registers and must be renormalised to s32 before the
   64-bit and; the set path needs none because sllv already sign-extends. */

void Bit64Assign_33de80(s64 *p0, s32 p1, s32 p2)
{
    if (p2 != 0) {
        *p0 |= 1 << p1;
    } else {
        *p0 &= ~(1 << p1);
    }
}
