#include "types.h"

/* Call the worker and report 0x1 unconditionally.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

extern void InsectCageMenuPairErrorMsgClose_38e910(s32, s32);

s32 InsectCageMenuPairErrorMsgCloseFwd_38e8f0(s32 p0, s32 p1)
{
    InsectCageMenuPairErrorMsgClose_38e910(p0, p1);
    return 0x1;
}
