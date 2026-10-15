#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern u8 D_0048361C;
extern s16 D_00483620;

void LeaderSwitchMenuReset_39d160(void)
{
    D_00483620 = 0;
    D_0048361C = 0;
}
