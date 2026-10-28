/* rgp:protos */
#define RGP_SELF_SaveSetLastSlot_376210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern s32 D_00483190;
extern s32 D_00483194;

void SaveSetLastSlot_376210(s32 o, s32 p1)
{
    D_00483190 = o;
    D_00483194 = p1;
}
