/* rgp:protos */
#define RGP_SELF_CharaDataReleaseSubRecsByKey_1ed750 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CharaDataReleaseSubRecsByKey_1ed750(s32 p0, s32 p1, s32 p2)
{
    s32 r0;

    if (p2 != 0) {
        r0 = CharaDataFindById_1ed990(p0, p1);
        if (r0 != 0) {
            CharaDataRecReleaseSubRecsByKey_1ee050(r0, p2);
        }
        return;
    }
}
