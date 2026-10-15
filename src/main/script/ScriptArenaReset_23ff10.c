#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern s32 D_00481EF0;
extern s32 D_00481EF4;

void ScriptArenaReset_23ff10(void)
{
    D_00481EF4 = D_00481EF0;
}
