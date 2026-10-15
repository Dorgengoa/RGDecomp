#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00156a00 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
    u8 pad00C[0xA4];
    s32 mB0;         /* +0xB0 */
} Obj_FUN_00156a00;

void ShadowMapDescInit_156a00(Obj_FUN_00156a00 *o)
{
    o->m00 = 0x3E800000;
    o->mB0 = 0;
    o->m04 = 0;
    o->m08 = 0;
}
