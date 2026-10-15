#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001ccc10 {
    s16 m00;         /* +0x0 */
    s16 m02;         /* +0x2 */
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
} Obj_FUN_001ccc10;

void LoadHandleReset_1ccc10(Obj_FUN_001ccc10 *o)
{
    o->m00 = -1;
    o->m02 = -1;
    o->m04 = 0;
    o->m08 = 0;
}
