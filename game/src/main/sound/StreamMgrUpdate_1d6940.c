/* rgp:protos */
#define RGP_SELF_StreamMgrUpdate_1d6940 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void StreamMgrUpdate_1d6940(s32 p0, f32 fa0)
{
    s32 l0;
    s32 l1;

    l1 = 0;
    do {
        StreamChanUpdate_1d72d0((p0 + (((l1 << 3) - l1) << 5)), fa0);
        l0 = ((l1 + 1) < 4);
        l1 = (l1 + 1);
    } while (l0 != 0);
}
