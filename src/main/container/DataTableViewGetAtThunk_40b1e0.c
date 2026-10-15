/* DataTableViewGetAtThunk_40b1e0 -- shape-identical to merged CharaMgrPoolViewCountThunk_3b09c0 (2 instructions); the donor's
   source with the symbol renamed, 1 call target(s) and 1 immediate(s) substituted:
     CharaMgrPoolCount_3a8260 -> func_0040B050
     imm -4 -> -136
   Found by build/zz/s23_xclone.py. */
#include "types.h"

extern void func_0040B050(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void DataTableViewGetAtThunk_40b1e0(s32 p0)
{
    func_0040B050((p0 + -136));
}
