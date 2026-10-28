/* rgp:protos */
#define RGP_SELF_DepthProbeSlotsReset_13fcb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void DepthProbeSlotsReset_13fcb0(s32 p0)
{
    s32 l0;

    l0 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l0 << 4) + 0x3CD0) = 1;
        *(s32 *)((u8 *)p0 + (l0 << 4) + 0x3CDC) = -1;
        l0 = (l0 + 1);
    } while (l0 < 4);
}
