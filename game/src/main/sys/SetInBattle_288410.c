/* rgp:protos */
#define RGP_SELF_SetInBattle_288410 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern u8 D_004821B8;

void SetInBattle_288410(void)
{
    D_004821B8 = 1;
}
