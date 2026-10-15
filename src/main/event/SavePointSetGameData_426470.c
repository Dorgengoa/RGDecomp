#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern s32 D_00483F38;

s32 SavePointSetGameData_426470(s32 o)
{
    D_00483F38 = o;
    return 1;
}
