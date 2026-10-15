#include "types.h"

/* Call the worker and truncate its result to u8.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

extern s32 ItemWeaponIsInFieldImpl_3d3c50(void);

u8 ItemWeaponIsInField_3d3220(void)
{
    return (u8)ItemWeaponIsInFieldImpl_3d3c50();
}
