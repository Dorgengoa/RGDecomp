#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002a02e0 {
    u8 pad000[0x38];
    s32 m38;         /* +0x38 */
} Obj_FUN_002a02e0;

s32 MenuSetSelItem_2a02e0(Obj_FUN_002a02e0 *o, s32 p1)
{
    o->m38 = p1;
    return 1;
}
