#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00312390 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    s16 m08;         /* +0x8 */
    s16 m0A;         /* +0xA */
} Obj_FUN_00312390;

void CharaRefReset_312390(Obj_FUN_00312390 *o)
{
    o->m00 = 0;
    o->m0A = -1;
    o->m04 = 0;
    o->m08 = 0;
}
