#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001954c0 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
} Obj_FUN_001954c0;

Obj_FUN_001954c0 * ModelAttachSlotCtor_1954c0(Obj_FUN_001954c0 *o)
{
    o->m04 = -1;
    o->m00 = -1;
    return o;
}
