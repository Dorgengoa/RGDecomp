#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0014d3a0 {
    u8 pad000[0x30];
    s32 m30;         /* +0x30 */
    u8 pad034[0x8];
    s32 m3C;         /* +0x3C */
} Obj_FUN_0014d3a0;

void MemStackResetMark_14d3a0(Obj_FUN_0014d3a0 *o)
{
    o->m30 = -1;
    o->m3C = 0;
}
