/* rgp:protos */
#define RGP_SELF_TransporterWarpFlagTest_27a930 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern u8 D_00482178;

s32 TransporterWarpFlagTest_27a930(void)
{
    return (D_00482178 & 1);
}
