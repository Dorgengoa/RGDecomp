#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern s32 D_00482898;
extern s32 D_0048289C;

void EventScratchRewind_301db0(void)
{
    D_0048289C = D_00482898;
}
