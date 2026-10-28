/* rgp:protos */
#define RGP_SELF_MapMgrSlotsFindEntryByKeyMaybe_1e15f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapMgrSlotsFindEntryByKeyMaybe_1e15f0(s32 p0, s32 p1)
{
    s32 r2;
    s32 l1;
    s32 l0;

    l0 = 0;
    l1 = (p0 + 0x1928);
    while (l0 < 4) {
        r2 = MapAreaActiveBlocksFindEntryByKeyMaybe_1d9150(l1, p1);
        if (r2 != 0) {
            return r2;
        }
        l0 = (l0 + 1);
        l1 = (l1 + 0x1CC);
    }
    return 0;
}
