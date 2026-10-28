/* rgp:protos */
#define RGP_SELF_DynCollisionIdCmd_167770 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Call the worker, keep its result in the small-data D_00481180,
   and report 0x1 unconditionally.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

extern s32 D_00481180;
/*rgp*/

s32 DynCollisionIdCmd_167770(s32 p0)
{
    D_00481180 = VariantGetInt_15f780(p0);
    return 0x1;
}
