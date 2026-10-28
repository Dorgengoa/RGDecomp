/* rgp:protos */
#define RGP_SELF_AlignUp16_1cacd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

s32 AlignUp16_1cacd0(s32 o)
{
    return ((o + 0xF) & -0x10);
}
