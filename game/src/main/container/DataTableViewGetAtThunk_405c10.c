/* rgp:protos */
#define RGP_SELF_DataTableViewGetAtThunk_405c10 1
#include "port/game_protos.h"
#line 1
/* DataTableViewGetAtThunk_405c10 -- shape-identical to merged CharaMgrPoolViewCountThunk_3b09c0 (2 instructions); the donor's
   source with the symbol renamed, 1 call target(s) and 1 immediate(s) substituted:
     CharaMgrPoolCount_3a8260 -> func_00405B40
     imm -4 -> -136
   Found by build/zz/s23_xclone.py. */
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void DataTableViewGetAtThunk_405c10(s32 p0, int rgp_a1)
{
    func_00405B30_e1((p0 + -136), (int)rgp_a1);
}
