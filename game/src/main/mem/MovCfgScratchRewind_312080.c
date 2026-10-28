/* rgp:protos */
#define RGP_SELF_MovCfgScratchRewind_312080 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern s32 D_004829B0;
extern s32 D_004829B4;

void MovCfgScratchRewind_312080(void)
{
    D_004829B4 = D_004829B0;
}
