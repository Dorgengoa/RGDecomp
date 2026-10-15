#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002d9240 {
    u8 m00;         /* +0x0 */
    u8 pad001[0x3];
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
} Obj_FUN_002d9240;

void MapNodeFadeInitMaybe_2d9240(Obj_FUN_002d9240 *o)
{
    o->m00 = 1;
    o->m04 = 1;
    o->m08 = 0;
}
