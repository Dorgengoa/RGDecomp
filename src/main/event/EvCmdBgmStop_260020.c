#include "types.h"

extern s32 BgmPlayTrack_2075e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdBgmStop_260020(void)
{
    s32 r;

    r = BgmPlayTrack_2075e0(0, 1);
    return 1;
}
