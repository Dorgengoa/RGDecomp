#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0023a2a0 {
    u8 pad000[0x7C];
    s32 m7C;         /* +0x7C */
} Obj_FUN_0023a2a0;

void CharaHangLedgeInvalidate_23a2a0(Obj_FUN_0023a2a0 *o)
{
    o->m7C = 0x80000000;
}
