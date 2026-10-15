#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001c73b0 {
    u8 pad000[0x20];
    f32 m20;         /* +0x20 */
    f32 m24;         /* +0x24 */
    f32 m28;         /* +0x28 */
    s32 m2C;         /* +0x2C */
} Obj_FUN_001c73b0;

void SrtSetPos_1c73b0(Obj_FUN_001c73b0 *o, f32 fa0, f32 fa1, f32 fa2)
{
    o->m20 = fa0;
    o->m24 = fa1;
    o->m28 = fa2;
    o->m2C = 0x3F800000;
}
