#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003c9790 {
    u8 pad000[0x108];
    s16 m108;         /* +0x108 */
    u8 pad10A[0x2];
    f32 m10C;         /* +0x10C */
} Obj_FUN_003c9790;

s32 PartySetNearestFuncPoint_3c9790(Obj_FUN_003c9790 *o, s32 p1, f32 fa0)
{
    o->m108 = p1;
    o->m10C = fa0;
    return 1;
}
