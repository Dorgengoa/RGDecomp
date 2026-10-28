/* rgp:protos */
#define RGP_SELF_CharaDataCollectNodes_1ed670 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CharaDataCollectNodes_1ed670(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    s32 r0;
    s32 r1;

    r0 = CharaDataFindSubRecById_1ed710(p0, p1, p2);
    if (r0 == 0) {
        return 0;
    }
    r1 = CharaDataSubRecCollectNodes_1ee640(r0, p3, p4, p5);
    return r1;
}
