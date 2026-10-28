/* rgp:protos */
#define RGP_SELF_EvCmdCharaHoldEnable_25a830 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045EE70[];

s32 EvCmdCharaHoldEnable_25a830(void)
{
    s32 r;

    r = TaskSetEnabled_27c2a0(1, D_0045EE70);
    return 1;
}
