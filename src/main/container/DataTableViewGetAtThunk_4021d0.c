#include "types.h"

extern void DataTableViewGetAt_401f10(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void DataTableViewGetAtThunk_4021d0(s32 p0, s32 p1)
{
    DataTableViewGetAt_401f10((p0 + -0x88), p1);
}
