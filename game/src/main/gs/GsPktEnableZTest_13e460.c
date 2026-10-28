/* rgp:protos */
#define RGP_SELF_GsPktEnableZTest_13e460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void GsPktEnableZTest_13e460(s32 p0, s32 p1)
{
    if (p1 == 0) {
        GsTestSetZTest_156f40((p0 + 0x10), 0);
    } else {
        GsTestSetZTest_156f40((p0 + 0x10), 2);
    }
}
