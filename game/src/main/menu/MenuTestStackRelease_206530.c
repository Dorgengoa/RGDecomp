/* rgp:protos */
#define RGP_SELF_MenuTestStackRelease_206530 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481BE4;
extern u8 D_004BBE00[];

void MenuTestStackRelease_206530(void)
{
    RecStackSlotRelease_201d10(D_004BBE00, &D_00481BE4);
}
