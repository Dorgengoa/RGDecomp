#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001ef470 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
} Obj_FUN_001ef470;

Obj_FUN_001ef470 * ModelObjExMemberCtorZero3Related_1ef470(Obj_FUN_001ef470 *o)
{
    o->m00 = 0;
    o->m04 = 0;
    o->m08 = 0;
    return o;
}
