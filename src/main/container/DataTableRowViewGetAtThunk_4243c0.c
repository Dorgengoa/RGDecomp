#include "types.h"

extern void DataTableRowViewGetAt_423530(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void DataTableRowViewGetAtThunk_4243c0(s32 p0, s32 p1)
{
    DataTableRowViewGetAt_423530((p0 + -4), p1);
}
