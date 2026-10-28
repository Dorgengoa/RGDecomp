/* rgp:protos */
#define RGP_SELF_ItemWeaponIsInField_3d3220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Call the worker and truncate its result to u8.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

/*rgp*/

u32 ItemWeaponIsInField_3d3220(void)
{
    return (u8)((u8)ItemWeaponIsInFieldImpl_3d3c50());
}
