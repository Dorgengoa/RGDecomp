#include "types.h"

/* Call the worker and truncate its result to u8.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

extern s32 UnitClampVitalsThunk_3ae430(s32);

u8 UnitClampVitalsThunk_3a9910(s32 p0)
{
    return (u8)UnitClampVitalsThunk_3ae430(p0);
}
