/* rgp:protos */
#define RGP_SELF_TargetMngHasTargetId_313bf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482A4C;

u8 TargetMngHasTargetId_313bf0(void)
{
    return (D_00482A4C >= 0);
}
