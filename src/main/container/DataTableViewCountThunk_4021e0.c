#include "types.h"

extern void DataTableGetCount_401dc0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void DataTableViewCountThunk_4021e0(s32 p0)
{
    DataTableGetCount_401dc0((p0 + -0x88));
}
