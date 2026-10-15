#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0018fbf0 {
    u8 pad000[0x4];
    s32 m04;         /* +0x4 */
} Obj_FUN_0018fbf0;

Obj_FUN_0018fbf0 * FuncDataTableCtor_18fbf0(Obj_FUN_0018fbf0 *o)
{
    o->m04 = 0;
    return o;
}
