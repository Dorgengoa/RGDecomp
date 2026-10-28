/* rgp:protos */
#define RGP_SELF_FrameCounterInc_1c6b00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern s64 D_00481630;

void FrameCounterInc_1c6b00(void)
{
    D_00481630 = (D_00481630 + 1);
}
