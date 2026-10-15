#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002d1c40 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
} Obj_FUN_002d1c40;

Obj_FUN_002d1c40 * NavMgrPoolArrayCtor_2d1c40(Obj_FUN_002d1c40 *o)
{
    o->m00 = 0;
    o->m04 = 0;
    o->m00 = 0;
    o->m04 = 0;
    o->m00 = 0;
    o->m04 = 0;
    return o;
}
