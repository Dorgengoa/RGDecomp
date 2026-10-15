/* UnitOnDamagedByThunkMaybe_3bc9d0 -- shape-identical to merged KernelExitThunk_120d18 (1 instructions); the donor's
   source with the symbol renamed, 1 call target(s) and 0 immediate(s) substituted:
     KernelExit_120d18 -> UnitBaseOnDamagedByMaybe_3b1390
   Found by build/zz/s23_xclone.py. */
#include "types.h"

extern void UnitBaseOnDamagedByMaybe_3b1390(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void UnitOnDamagedByThunkMaybe_3bc9d0(s32 p0)
{
    UnitBaseOnDamagedByMaybe_3b1390(p0);
}
