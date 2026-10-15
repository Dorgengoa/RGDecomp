#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

u32 BytesToQwords_18a6c0(s32 p0)
{
    if ((p0 & 0xF) != 0) {
        return ((((u32)p0) >> 4) + 1);
    }
    return (((u32)p0) >> 4);
}
