#include "types.h"

extern void VecCopyAsDir_1cbe20(s32, s32);
extern void VecCopyAsPoint_1cbe10(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void SrtCopyTo_1c7250(s32 p0, s32 p1)
{
    VecCopyAsDir_1cbe20(p1, p0);
    VecCopyAsDir_1cbe20((p1 + 0x10), (p0 + 0x10));
    VecCopyAsPoint_1cbe10((p1 + 0x20), (p0 + 0x20));
    VecCopyAsDir_1cbe20((p1 + 0x30), (p0 + 0x30));
    VecCopyAsDir_1cbe20((p1 + 0x40), (p0 + 0x40));
}
