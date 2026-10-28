/* rgp:protos */
#define RGP_SELF_SynopsisStackRelease_206b10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481B9C;
extern u8 D_004BB950[];

void SynopsisStackRelease_206b10(void)
{
    RecStackSlotRelease_201d10(D_004BB950, &D_00481B9C);
}
