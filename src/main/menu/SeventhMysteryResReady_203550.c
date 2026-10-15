#include "types.h"

extern s32 SeventhMysteryResPollThunk_395560(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

u8 SeventhMysteryResReady_203550(void)
{
    s32 r;

    r = SeventhMysteryResPollThunk_395560();
    return (r != 0);
}
