/* rgp:protos */
#define RGP_SELF_EventPendingPacketClear_3e25e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048399C;
extern u8 D_004E9740[];

s32 EventPendingPacketClear_3e25e0(void)
{
    s32 r;

    D_0048399C = 0;
    r = ((s32)ActionPacketClear_3e3e90(D_004E9740));
    return 1;
}
