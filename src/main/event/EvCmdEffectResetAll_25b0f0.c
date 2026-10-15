#include "types.h"

/* Call the worker and report 0x1 unconditionally.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

extern void EffectResetAll_2d8900(void);

s32 EvCmdEffectResetAll_25b0f0(void)
{
    EffectResetAll_2d8900();
    return 0x1;
}
