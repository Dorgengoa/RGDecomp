#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003b6450 {
    u8 pad000[0x1D8];
    s16 m1D8;         /* +0x1D8 */
} Obj_FUN_003b6450;

s32 CharaActFailCountReset_3b6450(Obj_FUN_003b6450 *o)
{
    o->m1D8 = 0;
    return 1;
}
