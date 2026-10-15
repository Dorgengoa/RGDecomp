#include "types.h"

extern void DataTableViewGetAt_424150(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void DataTableViewGetAtThunk_424420(s32 p0, s32 p1)
{
    DataTableViewGetAt_424150((p0 + -0x88), p1);
}
