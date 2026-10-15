/* CharaIsNotDeadThunk_3ac970 -- shape-identical to merged KernelExitThunk_120d18 (1 instructions); the donor's
   source with the symbol renamed, 1 call target(s) and 0 immediate(s) substituted:
     KernelExit_120d18 -> CharaIsNotDead_3b66f0
   Found by build/zz/s23_xclone.py. */
#include "types.h"

extern void CharaIsNotDead_3b66f0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CharaIsNotDeadThunk_3ac970(s32 p0)
{
    CharaIsNotDead_3b66f0(p0);
}
