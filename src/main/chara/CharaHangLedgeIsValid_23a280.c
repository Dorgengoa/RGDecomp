#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0023a280 {
    u8 pad000[0x7C];
    s32 m7C;         /* +0x7C */
} Obj_FUN_0023a280;

s32 CharaHangLedgeIsValid_23a280(Obj_FUN_0023a280 *o)
{
    return (((o->m7C & 0x80000000) != 0) ^ 1);
}
