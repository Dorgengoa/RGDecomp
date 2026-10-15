#include "types.h"

extern s32 MainMenuSetState_390d60(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 InsectCageMenuExit_390320(void)
{
    s32 r;

    r = MainMenuSetState_390d60(0xAD);
    return 1;
}
