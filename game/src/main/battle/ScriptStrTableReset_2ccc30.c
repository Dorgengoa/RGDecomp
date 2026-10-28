/* rgp:protos */
#define RGP_SELF_ScriptStrTableReset_2ccc30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern s32 D_004825DC;
extern s32 D_004825E0;

void ScriptStrTableReset_2ccc30(void)
{
    D_004825DC = 0;
    D_004825E0 = 0;
}
