/* rgp:protos */
#define RGP_SELF_SoundStreamSetOutputMode_1bc6e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern s32 D_0047E20C;

void SoundStreamSetOutputMode_1bc6e0(s32 o)
{
    D_0047E20C = (o & 0xFF);
}
