/* rgp:protos */
#define RGP_SELF_SoundMakeId_1bbf30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

s32 SoundMakeId_1bbf30(s32 o, s32 p1)
{
    return ((o & 0xFFFF0000) | (p1 & 0xFFFF));
}
