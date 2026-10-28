/* rgp:protos */
#define RGP_SELF_MapMgrCaptionLoad_1e2f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

int MapMgrCaptionLoad_1e2f10(s32 p0, s32 p1, s32 p2)
{
    s32 r0;

    r0 = ((s32)GetReadBuffHeap_2025e0());
    return MapCaptionLoad_33fa90((p0 + 0x18E8), p1, r0, p2);
}
