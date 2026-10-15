#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00157560 {
    u8 pad000[0xC];
    s32 m0C;         /* +0xC */
    s32 m10;         /* +0x10 */
} Obj_FUN_00157560;

void DrawEnvSetCenter_157560(Obj_FUN_00157560 *o, s32 p1, s32 p2)
{
    o->m0C = (p1 + 0x800);
    o->m10 = (p2 + 0x800);
}
