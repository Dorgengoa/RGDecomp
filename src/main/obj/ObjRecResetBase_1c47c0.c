#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001c47c0 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    u8 m08;         /* +0x8 */
    u8 pad009[0xF];
    s16 m18;         /* +0x18 */
    s16 m1A;         /* +0x1A */
    s32 m1C;         /* +0x1C */
} Obj_FUN_001c47c0;

void ObjRecResetBase_1c47c0(Obj_FUN_001c47c0 *o)
{
    o->m00 = 0;
    o->m08 = 0;
    o->m1C = 0;
    o->m18 = -1;
    o->m1A = 0;
    o->m04 = 0;
}
