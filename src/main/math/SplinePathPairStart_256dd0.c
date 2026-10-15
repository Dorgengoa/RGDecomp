#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00256dd0 {
    u8 pad000[0x940];
    s32 m940;         /* +0x940 */
} Obj_FUN_00256dd0;

void SplinePathPairStart_256dd0(Obj_FUN_00256dd0 *o)
{
    o->m940 = 1;
}
