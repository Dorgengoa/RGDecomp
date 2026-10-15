#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002a4e20 {
    u8 pad000[0x18];
    s32 m18;         /* +0x18 */
} Obj_FUN_002a4e20;

s32 MenuSetSelMode_2a4e20(Obj_FUN_002a4e20 *o, s32 p1)
{
    o->m18 = p1;
    return 1;
}
