#include "types.h"

extern void DataTableViewGetAt_40b110(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void DataTableViewGetAtThunk_40b200(s32 p0, s32 p1)
{
    DataTableViewGetAt_40b110((p0 + -0x88), p1);
}
