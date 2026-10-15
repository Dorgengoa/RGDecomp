#include "types.h"

/* Call the worker and report 0x1 unconditionally.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

extern void InsectCageMenuInfoClose_38fd10(s32, s32);

s32 InsectCageMenuInfoCloseFwd_38fcf0(s32 p0, s32 p1)
{
    InsectCageMenuInfoClose_38fd10(p0, p1);
    return 0x1;
}
