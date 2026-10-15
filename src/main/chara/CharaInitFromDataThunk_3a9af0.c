#include "types.h"

/* Call the worker and truncate its result to u8.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

extern s32 CharaInitFromData_3af8f0(s32, s32, s32);

u8 CharaInitFromDataThunk_3a9af0(s32 p0, s32 p1, s32 p2)
{
    return (u8)CharaInitFromData_3af8f0(p0, p1, p2);
}
