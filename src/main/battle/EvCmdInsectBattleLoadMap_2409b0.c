#include "types.h"

/* Call the worker and report 0x1 unconditionally.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

extern void InsectBattleLoadMap_31a1a0(void);

s32 EvCmdInsectBattleLoadMap_2409b0(void)
{
    InsectBattleLoadMap_31a1a0();
    return 0x1;
}
