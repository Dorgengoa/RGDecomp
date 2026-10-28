/* rgp:protos */
#define RGP_SELF_MinimapMgrRefreshAll_3219a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MinimapMgrRefreshAll_3219a0(s32 p0)
{
    s32 l0;
    s32 r1;

    l0 = 0;
    do {
        r1 = MinimapSlotIsActive_322510((p0 + (((l0 * 0x24) - (l0 * 0x9)) << 4)));
        if (r1 != 0) {
            MinimapRefreshPos_324950((p0 + (((l0 * 0x24) - (l0 * 0x9)) << 4)));
        }
        l0 = (l0 + 1);
    } while (l0 < 3);
    return 1;
}
