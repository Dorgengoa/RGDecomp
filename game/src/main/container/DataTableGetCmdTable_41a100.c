/* rgp:protos */
#define RGP_SELF_DataTableGetCmdTable_41a100 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00467D20[];

void *DataTableGetCmdTable_41a100(void)
{
    return D_00467D20;
}
