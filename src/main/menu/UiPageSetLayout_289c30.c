#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00289c30 {
    s32 m00;         /* +0x0 */
} Obj_FUN_00289c30;

s32 UiPageSetLayout_289c30(Obj_FUN_00289c30 *o, s32 p1)
{
    o->m00 = p1;
    return 1;
}
