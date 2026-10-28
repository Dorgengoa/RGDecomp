/* rgp:protos */
#define RGP_SELF_GoTitleMenuReset_39bf30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern u8 D_00483624;
extern s16 D_00483628;

void GoTitleMenuReset_39bf30(void)
{
    D_00483628 = 0;
    D_00483624 = 0;
}
