#include "types.h"

extern void PlayMenuSe_289ef0(s32);
extern s32 SeventhMysteryCursorPlace_3948a0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 SeventhMysteryCursorMoveCb_394a50(s32 p0)
{
    s32 r1;

    PlayMenuSe_289ef0(4);
    r1 = SeventhMysteryCursorPlace_3948a0(p0);
    return 1;
}
