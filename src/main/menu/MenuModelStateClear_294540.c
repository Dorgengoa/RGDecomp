#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern u8 D_00482398;
extern s32 D_004823D0;

void MenuModelStateClear_294540(void)
{
    D_004823D0 = 0;
    D_00482398 = 0;
}
