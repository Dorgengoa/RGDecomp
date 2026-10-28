/* rgp:protos */
#define RGP_SELF_SoundStreamSlotThreadPause_1bd670 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern s32 D_0048150C;

void SoundStreamSlotThreadPause_1bd670(void)
{
    D_0048150C = 1;
}
