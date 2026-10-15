#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481F38;

void EventSoundBankHandleSet_24fca0(s32 p0, s32 p1)
{
    *(s32 *)((u8 *)&D_00481F38 + (p1 << 2)) = p0;
}
