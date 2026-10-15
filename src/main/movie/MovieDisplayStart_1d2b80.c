#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern s32 D_004817A0;
extern u8 D_004817D4;

void MovieDisplayStart_1d2b80(void)
{
    D_004817A0 = 0;
    D_004817D4 = 1;
}
