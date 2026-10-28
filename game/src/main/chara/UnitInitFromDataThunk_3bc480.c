/* rgp:protos */
#define RGP_SELF_UnitInitFromDataThunk_3bc480 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Call the worker and truncate its result to u8.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

/*rgp*/

u8 UnitInitFromDataThunk_3bc480(s32 p0, s32 p1, s32 p2)
{
    return (u8)UnitInitFromData_3be710(p0, p1, p2);
}
